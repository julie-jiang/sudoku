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
        HashTable();
        HashTable(size_t);
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
        std::hash<std::string> hashFunction;
        size_t getIndex(Key);
        int hash(Key);
        std::string toString(Key);
};

/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/
#include <functional>
#include <sstream>

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable()
{
    bucketSize = 100;
    buckets = new Node *[bucketSize];
    for (size_t i = 0; i < bucketSize; i++) {
        buckets[i] = nullptr;
    }
    hashFunction = std::hash<std::string>{};
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size)
{
    bucketSize = size;
    buckets = new Node *[bucketSize];
    for (size_t i = 0; i < bucketSize; i++) {
        buckets[i] = nullptr;
    }
    hashFunction = std::hash<std::string>{};
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
    //std::cout << "Trying to set value for key " << k << std::endl;
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
    //std::cout << "Trying to get value for key " << k << std::endl;
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
    return hash(k) % bucketSize;
}

template<typename Key, typename Value>
int HashTable<Key, Value>::hash(Key k)
{
    std::string stringK = toString(k);
    return hashFunction(stringK);


}
template<typename Key, typename Value>
std::string HashTable<Key, Value>::toString(Key k)
{
    std::string result;
    std::ostringstream oss;
    oss << k;
    result = oss.str();
    return result;
}



#endif