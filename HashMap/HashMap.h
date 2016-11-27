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
#include <functional>
#include <sstream>
#include "LinkedList/LinkedList.h"
#include "../Set/Set.h"
#include "../Set/SetIterator.h"
template<typename Key, typename Value>

class HashMap {

    public:
        typedef SetIterator<Key> key_iterator;
        HashMap();
        HashMap(size_t);
        ~HashMap();
        Value &operator[](const Key &);
        void insert(Key, Value);
        void remove(Key);
        key_iterator begin();
        key_iterator end();
    private:
        Set<Key> *linkedHashKeys;
        LinkedList<Key, Value> **buckets;
        std::hash<std::string> hashFunction;
        
        size_t bucketSize;

        void init();
        size_t getIndex(Key);
        std::string toString(Key);
};

/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/


template<typename Key, typename Value>
HashMap<Key, Value>::HashMap()
{
    bucketSize = 100;
    init();
}
template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap()
{
    for (size_t i = 0; i < bucketSize; i++) {
        delete buckets[i];
    }

}

template<typename Key, typename Value>
SetIterator<Key> HashMap<Key, Value>::begin()
{
    return linkedHashKeys->begin();
}

template<typename Key, typename Value>
SetIterator<Key> HashMap<Key, Value>::end()
{
    return linkedHashKeys->end();
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
        buckets[i] = new LinkedList<Key, Value>();
    }
    hashFunction = std::hash<std::string>{};
    linkedHashKeys = new Set<Key>();
}

template<typename Key, typename Value>
void HashMap<Key, Value>::insert(Key k, Value val)
{
    buckets[getIndex(k)]->insert(k, val);
    linkedHashKeys->add(k);
    
}

template<typename Key, typename Value>
Value &HashMap<Key, Value>::operator[](const Key &k)
{
    return (*buckets[getIndex(k)])[k];
}

template<typename Key, typename Value>
void HashMap<Key, Value>::remove(Key k)
{
    if (buckets[getIndex(k)]->remove(k)) {
        linkedHashKeys->remove(k);
    }
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::getIndex(Key k)
{
    return hashFunction(toString(k)) % bucketSize;
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