

/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <functional>
#include <sstream>
#include <stack>
#include "LinkedList/LinkedList.h"
#include "HTIterator.h"
template<typename Key, typename Value>

class HashTable {

    public:
        HashTable(size_t = 100);
        HashTable(const HashTable &);
        ~HashTable();
        HashTable &operator=(const HashTable &);
        Value &operator[](const Key &) const;
        void insert(Key, Value);
        void remove(Key);
        typedef HTIterator<Key, Value> iterator;
        iterator begin() const;
        iterator end() const;
        void clear();
        void resize(size_t);
        
    private:
        LinkedList<Key, Value> **buckets;
        std::hash<std::string> hashFunction;
        size_t num_buckets;
        size_t num_elements;
        const float kLoadFactor = 0.75;


        void init();
        size_t getIndex(Key) const;
        std::string toString(Key) const;
        void deepCopy(const HashTable &);

};
/*****************************************************************************/
/*           Big Three, Initialization and other helper functions            */
/*****************************************************************************/

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size)
{
    num_buckets = size;
    init();
}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable()
{
    for (size_t i = 0; i < num_buckets; i++) {
        delete buckets[i];
    }
    delete buckets;
}
template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable &source)
{
    this->num_buckets = source.num_buckets;
    init();
    deepCopy(source);
}
template<typename Key, typename Value>
HashTable<Key, Value> &HashTable<Key, Value>::operator=(const HashTable &source)
{
    clear();
    this->num_buckets = source.num_buckets;
    init();
    deepCopy(source);
    return *this;
}

template<typename Key, typename Value>
void HashTable<Key, Value>::clear()
{
    std::stack<Key> *keys = new std::stack<Key>;
    for (HashTable<Key, Value>::iterator it = this->begin(); 
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
void HashTable<Key, Value>::deepCopy(const HashTable &source)
{
    for (HashTable<Key, Value>::iterator it = source.begin(); 
         it != source.end(); ++it) {
        insert(it.key(), it.value());
    }

}
template<typename Key, typename Value>
void HashTable<Key, Value>::resize(size_t new_size)
{
    HashTable<Key, Value> ht_original = *this;
    clear();
    this->num_buckets = new_size;
    init();
    deepCopy(ht_original);

}
template<typename Key, typename Value>
void HashTable<Key, Value>::init()
{
    buckets = new LinkedList<Key, Value> *[num_buckets];
    for (size_t i = 0; i < num_buckets; i++) {
        buckets[i] = new LinkedList<Key, Value>();
    }
    hashFunction = std::hash<std::string>{};
}

/*****************************************************************************/
/*                           Iterator functions                              */
/*****************************************************************************/
template<typename Key, typename Value>
HTIterator<Key, Value> HashTable<Key, Value>::begin() const
{
    return HTIterator<Key, Value>(buckets, num_buckets);
}
template<typename Key, typename Value>
HTIterator<Key, Value> HashTable<Key, Value>::end() const
{
    return HTIterator<Key, Value>(nullptr, num_buckets);
    
}



template<typename Key, typename Value>
void HashTable<Key, Value>::insert(Key k, Value val)
{
    if (buckets[getIndex(k)]->insert(k, val)) {
        num_elements++;
    }
    if ((float) num_elements / num_buckets > kLoadFactor) {
        resize((size_t) num_elements / kLoadFactor);
    }
}

template<typename Key, typename Value>
Value &HashTable<Key, Value>::operator[](const Key &k) const
{
    return (*buckets[getIndex(k)])[k];
}

template<typename Key, typename Value>
void HashTable<Key, Value>::remove(Key k)
{
    if (buckets[getIndex(k)]->remove(k)) {
        num_elements--;
    }
}

template<typename Key, typename Value>
size_t HashTable<Key, Value>::getIndex(Key k) const
{
    return hashFunction(toString(k)) % num_buckets;
}

template<typename Key, typename Value>
std::string HashTable<Key, Value>::toString(Key k) const
{
    std::ostringstream oss;
    oss << k;
    return oss.str();
}



#endif