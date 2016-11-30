

/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <functional>
#include <sstream>
#include <stack>
#include <math.h>
#include "../LinkedList/LinkedList.h"
#include "HTIterator.h"
template<typename Key, typename Value>

class HashTable {

    public:
        HashTable(size_t = 75);
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
        size_t numBuckets;
        size_t numElements;
        const float kLoadFactor = 0.75;


        void init();
        size_t getIndex(Key) const;
        std::string toString(Key) const;
        void deepCopy(const HashTable &);
        size_t getBucketSize(size_t);
        bool isPrime(size_t);

};
/*****************************************************************************/
/*           Big Three, Initialization and other helper functions            */
/*****************************************************************************/

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size)
{
    numBuckets = getBucketSize(size);
    init();
}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable()
{
    for (size_t i = 0; i < numBuckets; i++) {
        delete buckets[i];
    }
    delete buckets;
}
template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable &source)
{
    this->numBuckets  = source.numBuckets;
    init();
    deepCopy(source);
}
template<typename Key, typename Value>
HashTable<Key, Value> &HashTable<Key, Value>::operator=(const HashTable &source)
{
    clear();
    this->numBuckets = source.numBuckets;
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
        buckets[getIndex(it.key())]->insert(it.key(), it.value());
    }
    numElements = source.numElements;

}
template<typename Key, typename Value>
void HashTable<Key, Value>::resize(size_t size)
{
    HashTable<Key, Value> ht_original = *this;
    clear();
    this->numBuckets = getBucketSize(size);
    init();
    deepCopy(ht_original);

}
template<typename Key, typename Value>
void HashTable<Key, Value>::init()
{
    numElements = 0;
    buckets = new LinkedList<Key, Value> *[numBuckets];
    for (size_t i = 0; i < numBuckets; i++) {
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
    return HTIterator<Key, Value>(buckets, numBuckets);
}
template<typename Key, typename Value>
HTIterator<Key, Value> HashTable<Key, Value>::end() const
{
    return HTIterator<Key, Value>(nullptr, numBuckets);
    
}

template<typename Key, typename Value>
void HashTable<Key, Value>::insert(Key k, Value val)
{
    if (buckets[getIndex(k)]->insert(k, val)) {
        numElements++;
    }
    // Get the smallest prime number larger than numBuckets * 2
    if ((float) numElements / numBuckets > kLoadFactor) {
        resize(getBucketSize(numBuckets * 2));
    }
}
template<typename Key, typename Value>
size_t HashTable<Key, Value>::getBucketSize(size_t lower_bound)
{
    size_t num = lower_bound;
    while (not isPrime(num)) {
        num++;
    }
    return num;
}
template<typename Key, typename Value>
bool HashTable<Key, Value>::isPrime(size_t num)
{
    for (size_t i = 2; i < (size_t) sqrt(num) + 1; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
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
        numElements--;
    }
}

template<typename Key, typename Value>
size_t HashTable<Key, Value>::getIndex(Key k) const
{
    return hashFunction(toString(k)) % numBuckets;
}

template<typename Key, typename Value>
std::string HashTable<Key, Value>::toString(Key k) const
{
    std::ostringstream oss;
    oss << k;
    return oss.str();
}



#endif