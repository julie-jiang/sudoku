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

#ifndef HASHMAP_H
#define HASHMAP_H
#include "LinkedList/LinkedList.h"
template<typename Key, typename Value>

class HashMap {

    public:
        HashMap();
        HashMap(size_t);
        ~HashMap();
        Value &operator[](const Key);
        void set(Key, Value);
        Value get(Key);
    private:
        LinkedList<Key, Value> **buckets;
        size_t bucketSize;
        std::hash<std::string> hashFunction;

        void init();
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
HashMap<Key, Value>::HashMap()
{
    bucketSize = 100;
    init();
}

template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(size_t size)
{
    bucketSize = size;
    init();

}
template<typename Key, typename Value>
void HashMap<Key, Value>::init()
{
    buckets = new LinkedList<Key, Value> *[bucketSize];
    for (size_t i = 0; i < bucketSize; i++) {
        buckets[i] = nullptr;
    }
    hashFunction = std::hash<std::string>{};
}
template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap()
{

}


template<typename Key, typename Value>
void HashMap<Key, Value>::set(Key k, Value val)
{
    //std::cout << "Trying to set value for key " << k << std::endl;
    size_t index = getIndex(k);
    std::cout << "Hashed index " << index << std::endl;
    if (buckets[index] == nullptr) {
        buckets[index] = new LinkedList<Key, Value>();
        buckets[index]->insert(k, val);
        std::cout << "Set successfully\n";
    } else {
        buckets[index]->insert(k, val);
        std::cout << "Collision!\n";
    }


}
template<typename Key, typename Value>
Value HashMap<Key, Value>::get(Key k)
{
    //std::cout << "Trying to get value for key " << k << std::endl;
    size_t index = getIndex(k);
    std::cout << "Hashed index " << index << std::endl;
    if (buckets[index] != nullptr) {
        Value val = buckets[index]->get(k);
        std::cout << "Returning value " << val << std::endl;
        return val;
    } else {
        std::cout << "Value does not exist!\n";
        throw std::logic_error("");
    }

    
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::getIndex(Key k)
{
    return hash(k) % bucketSize;
}

template<typename Key, typename Value>
int HashMap<Key, Value>::hash(Key k)
{
    std::string stringK = toString(k);
    return hashFunction(stringK);


}
template<typename Key, typename Value>
std::string HashMap<Key, Value>::toString(Key k)
{
    std::string result;
    std::ostringstream oss;
    oss << k;
    result = oss.str();
    return result;
}



#endif