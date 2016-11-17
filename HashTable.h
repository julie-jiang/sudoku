/*
 * Hash table
 * 1) able to look up quickly given the key
 * 2) return some sort of none when key is not in table
 * 3) able to remove and insert keys quickly
 * 4) assume that resizing and rehashing is not necessary
 */

/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H

template<typename Key, typename Value>

class HashTable {

	public:
		HashTable(size_t size = 100);
		~HashTable();
		void set(Key, Value);
		Value get(Key);
	private:
		struct Node {
			Value val;
			Node *next;
		};
		Node **buckets;
		size_t bucketSize;
		size_t getIndex(Key);
		std::hash<Key> hashFunction;
};

/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/
#include <functional>

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size)
{
	bucketSize = size;
	buckets = new Node *[bucketSize];
	for (size_t i = 0; i < bucketSize; i++) {
		buckets[i] = nullptr;
	}
	hashFunction = std::hash<Key>{};
}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable()
{

}


template<typename Key, typename Value>
void HashTable<Key, Value>::set(Key k, Value val)
{
	Node *newNode = new Node;
	newNode->val = val;
	newNode->next = nullptr;
	std::cout << "Trying to set value for key " << k << std::endl;
	size_t index = getIndex(k);
	std::cout << "Hashed index " << index << std::endl;
	if (buckets[index] == nullptr) {
		buckets[index] = newNode;
		std::cout << "Set successfully\n";
	} else {
		buckets[index] = newNode;
		std::cout << "Collision!\n";
	}


}
template<typename Key, typename Value>
Value HashTable<Key, Value>::get(Key k)
{
	std::cout << "Trying to get value for key " << k << std::endl;
	size_t index = getIndex(k);
	std::cout << "Hashed index " << index << std::endl;
	if (buckets[index] != nullptr) {
		Value val = buckets[index]->val;
		std::cout << "Returning value " << val << std::endl;
		return val;
	} else {
		std::cout << "Value does not exist!\n";
		throw std::logic_error("");
	}

	
}

template<typename Key, typename Value>
size_t HashTable<Key, Value>::getIndex(Key k)
{
	return hashFunction(k) % bucketSize;
}




#endif