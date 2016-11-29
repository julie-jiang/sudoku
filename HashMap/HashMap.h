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
#include <stack>
#include "LinkedList/LinkedList.h"
#include "MapIterator.h"
template<typename Key, typename Value>

class HashMap {

    public:
        HashMap();
        HashMap(size_t);
        HashMap(const HashMap &);
        ~HashMap();
        HashMap &operator=(const HashMap &);
        Value &operator[](const Key &) const;
        void insert(Key, Value);
        void remove(Key);
        typedef MapIterator<Key, Value> iterator;
        iterator begin() const;
        iterator end() const;
        void clear();
        
    private:
        LinkedList<Key, Value> **buckets;
        std::hash<std::string> hashFunction;
        size_t num_buckets;
        size_t num_elements;


        void init();
        size_t getIndex(Key) const;
        std::string toString(Key) const;
        void deepCopy(const HashMap &);

};

/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/


template<typename Key, typename Value>
HashMap<Key, Value>::HashMap()
{
    num_buckets = 100;
    init();
}
template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(size_t size)
{
    num_buckets = size;
    init();

}
template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap()
{
    for (size_t i = 0; i < num_buckets; i++) {
        delete buckets[i];
    }
}
template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(const HashMap &source)
{
    this->num_buckets = source.num_buckets;
    init();
    deepCopy(source);
}
template<typename Key, typename Value>
HashMap<Key, Value> &HashMap<Key, Value>::operator=(const HashMap &source)
{
    this->num_buckets = source.num_buckets;
    clear();
    deepCopy(source);
    return *this;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::clear()
{
    std::stack<Key> *keys = new std::stack<Key>;
    for (HashMap<Key, Value>::iterator it = this->begin(); 
         it != this->end(); ++it) { 
        keys->push(it.key());
    }
    while (not keys->empty()) {
        Key k = keys->top();
        keys->pop();
        remove(k);
    }
    delete keys;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::deepCopy(const HashMap &source)
{
    for (HashMap<Key, Value>::iterator it = source.begin(); 
         it != source.end(); ++it) {
        insert(it.key(), it.value());
    }

}
template<typename Key, typename Value>
MapIterator<Key, Value> HashMap<Key, Value>::begin() const
{
    return MapIterator<Key, Value>(buckets, num_buckets);
}
template<typename Key, typename Value>
MapIterator<Key, Value> HashMap<Key, Value>::end() const
{
    return MapIterator<Key, Value>(nullptr, num_buckets);
    
}


template<typename Key, typename Value>
void HashMap<Key, Value>::init()
{
    buckets = new LinkedList<Key, Value> *[num_buckets];
    for (size_t i = 0; i < num_buckets; i++) {
        buckets[i] = new LinkedList<Key, Value>();
    }
    hashFunction = std::hash<std::string>{};
}

template<typename Key, typename Value>
void HashMap<Key, Value>::insert(Key k, Value val)
{
    if (buckets[getIndex(k)]->insert(k, val)) {
        num_elements++;
    }

    
}

template<typename Key, typename Value>
Value &HashMap<Key, Value>::operator[](const Key &k) const
{
    return (*buckets[getIndex(k)])[k];
}

template<typename Key, typename Value>
void HashMap<Key, Value>::remove(Key k)
{
    if (buckets[getIndex(k)]->remove(k)) {
        num_elements--;
    }
}

template<typename Key, typename Value>
size_t HashMap<Key, Value>::getIndex(Key k) const
{
    return hashFunction(toString(k)) % num_buckets;
}

template<typename Key, typename Value>
std::string HashMap<Key, Value>::toString(Key k) const
{
    std::ostringstream oss;
    oss << k;
    return oss.str();
}



#endif