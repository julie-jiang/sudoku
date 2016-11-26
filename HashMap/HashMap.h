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
template<typename Key, typename Value>

class HashMap {

    public:
        HashMap();
        HashMap(size_t);
        ~HashMap();
        Value &operator[](const Key &);
        void insert(Key, Value);
        void remove(Key);
        typedef ListIterator<Key, Value> iterator;
        iterator begin();
        iterator end();
    private:
        LinkedList<Key, Value> **buckets;
        std::hash<std::string> hashFunction;
        LinkedList<Key, Value> linkedHashMap;
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
ListIterator<Key, Value> HashMap<Key, Value>::begin()
{
    return linkedHashMap.begin();
}

template<typename Key, typename Value>
ListIterator<Key, Value> HashMap<Key, Value>::end()
{
    return linkedHashMap.end();
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
}

template<typename Key, typename Value>
void HashMap<Key, Value>::insert(Key k, Value val)
{
    buckets[getIndex(k)]->insert(k, val);
    linkedHashMap.insert(k, val);
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
        linkedHashMap.remove(k);
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