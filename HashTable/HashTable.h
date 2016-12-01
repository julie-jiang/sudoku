/* 
   HashTable.h
   Header and implementations of the container HashTable, an unordered 
   collection of elememts (or values) indexed by keys. 
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project                                     */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* A HashTable instance can be created with the default constructor, 
   a parameterized constructor that sets the size of the hash table to the 
   input number, or a copy constructor. Once created, you can
      (1) insert a key, value pair into the hash table
      (2) query for the value with a key using subscript operator
      (3) remove a key (and accordingly its value) from the hash table
      (4) resize the hash table
      (5) iterate through the hash table 
      
   Because values are indexed by keys, keys must be immutable, meaning they 
   cannot be changed. Values, however, can be changed or overwritten. Which 
   means that keys should be unique to ensure that no data is lost. Due to the
   way that the keys are hashed, the keys must also be able to be converted to
   a string.

   For more usage information and examples, please see the README.md in this 
   directory.                                                                */
/*****************************************************************************/
/*                         Implementation details                            */
/*****************************************************************************/
/* Hash collision is resolved by chaining. Therefore, the hash table is 
   implemented as a bunch of buckets, each bucket is a LinkedList object (see 
   LinkedList), which in turn holds a bunch of ListNodes. In order to reduce
   hash collisions, the size of the bucket is always a prime number. 

   When the load factor (defined to be the number of elements stored in the 
   hash table divided by the number of buckets) is larger than the threshold
   0.75, then the buckets will be resized to the smallest prime number 
   greater than bucketSize * 2. 

   The keys are hashed by their string form using the hash function included
   in <functional>.                                                          */
/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <functional>
#include <sstream>
#include <math.h>
#include "../LinkedList/LinkedList.h"
#include "HTIterator.h"
template<typename Key, typename Value>

class HashTable {

    public:
        // Default Constructor. Creates buckets with 101 slots.
        HashTable();
        // Parameterized Constructor. Creates at least "size" number of buckets
        HashTable(size_t size); 
        HashTable(const HashTable &);             // Copy constructor
        ~HashTable();       
        HashTable &operator=(const HashTable &);  // Assignment operator
        Value     &operator[](const Key &) const; // Subscript operator
        void      insert(Key, Value);             
        void      remove(Key);
        void      resize(size_t);                 
        typedef HTIterator<Key, Value> iterator;
        iterator  begin() const;
        iterator  end() const;
        
        
    private:
        LinkedList<Key, Value> **buckets;
        std::hash<std::string> hashFunction;
        size_t numBuckets;
        size_t numElements;
        const float kLoadFactorThreshold = 0.75;


        void        init();
        size_t      hash(Key) const;
        std::string toString(Key) const;
        void        copyAll(const HashTable &);
        size_t      getBucketSize(size_t);
        bool        isPrime(size_t);
        void        clear();

};
/*****************************************************************************/
/*                               Implementaions                              */
/*****************************************************************************/

/* Default constructor. 
   Initializes 101 buckets. This is a prime number chosen quite arbitrarily. */
template<typename Key, typename Value>
HashTable<Key, Value>::HashTable() {
    numBuckets = 101;  // Smallest prime number larger than 100.
    init();
}
/* Parameterized constructor. 
   Initializes at least "size" number of buckets. Bucket size is the smallest 
   prime number greater than or equal to "size". */
template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(size_t size) {

    // Get the smallest prime number larger than size
    numBuckets = getBucketSize(size); 
    init();
}
/* Copy constructor */
template<typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable &source) {
    this->numBuckets  = source.numBuckets;
    init();
    copyAll(source);
}

/* Assignment overload */
template<typename Key, typename Value>
HashTable<Key, Value> &HashTable<Key, Value>::operator=(
        const HashTable &source) {
    clear();
    this->numBuckets = source.numBuckets;
    init();
    copyAll(source);
    return *this;
}
/* Destructor */
template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable() {
    clear();
}


/* deletes everything */
template<typename Key, typename Value>
void HashTable<Key, Value>::clear() {
    for (size_t i = 0; i < numBuckets; i++) {
        delete buckets[i];
    }
    delete [] buckets;
}
/* Copies all elements in source by inserting all the key value pairs in 
   source into this hash table. */
template<typename Key, typename Value>
void HashTable<Key, Value>::copyAll(const HashTable &source) {

    for (HashTable<Key, Value>::iterator it = source.begin(); 
         it != source.end(); ++it) {
        buckets[hash(it.key())]->insert(it.key(), it.value());
    }
    numElements = source.numElements;

}
/* Resizes the hash table. This is done by re-inserting all key, value pairs 
   into a table of a new size. The new size is a prime number that is at least
   as large the given parameter. */
template<typename Key, typename Value>
void HashTable<Key, Value>::resize(size_t size) {
    HashTable<Key, Value> ht_original = *this;
    clear();
    this->numBuckets = getBucketSize(size);
    init();
    copyAll(ht_original);

}
/* Initializes private variables */
template<typename Key, typename Value>
void HashTable<Key, Value>::init() {
    numElements = 0;
    buckets = new LinkedList<Key, Value> *[numBuckets];
    for (size_t i = 0; i < numBuckets; i++) {
        buckets[i] = new LinkedList<Key, Value>();
    }
    hashFunction = std::hash<std::string>{};
}


/* Returns iterator to the beginning of the table */
template<typename Key, typename Value>
HTIterator<Key, Value> HashTable<Key, Value>::begin() const {
    return HTIterator<Key, Value>(buckets, numBuckets);
}
/* Returns iterator to the end of the table */
template<typename Key, typename Value>
HTIterator<Key, Value> HashTable<Key, Value>::end() const {
    return HTIterator<Key, Value>(nullptr, numBuckets);
    
}
/* Inserts key value pair to the hash table. If the key already exists, 
   then its value will be overwritten with the new val, and numElements will 
   not be incremented. 
   If after insertion the load factor exeeds the threshold, then the 
   table will be resized to hold at least double the current number of 
   buckets. */
template<typename Key, typename Value>
void HashTable<Key, Value>::insert(Key k, Value val) {
    if (buckets[hash(k)]->insert(k, val)) {
        numElements++;
    }
    // Get the smallest prime number larger than numBuckets * 2
    if ((float) numElements / numBuckets > kLoadFactorThreshold) {
        resize(getBucketSize(numBuckets * 2));
    }
}
/* Returns the smallest prime number greater than or equal to the loewr 
   bound. */
template<typename Key, typename Value>
size_t HashTable<Key, Value>::getBucketSize(size_t lower_bound) {
    size_t num = lower_bound;
    while (not isPrime(num)) {
        num++;
    }
    return num;
}
/* Returns true if the given number is a prime number. 
   A prime number is one that is only divisable by itself and 1. Therefore, 
   we check that the number does not have any factors greater than 1 and 
   smaller than itself. 
   The problem can be further reduced by only checking values up to sqrt(num).
   This is because any factor greater than sqrt(num) has a matching factor
   that is smaller than sqrt(num).  */
template<typename Key, typename Value>
bool HashTable<Key, Value>::isPrime(size_t num) {

    if (num == 1) {   // Special case 
        return false;
    }

    for (size_t i = 2; i < (size_t) sqrt(num) + 1; i++) {
        if (num % i == 0) {  // If i is a factor of num
            return false;
        }
    }
    return true;
}
/* Overloads subscript operator. Return the value associated with the given 
   key. Throws logic_error if key does not exist. */
template<typename Key, typename Value>
Value &HashTable<Key, Value>::operator[](const Key &k) const {
    return (*buckets[hash(k)])[k];
}
/* Removes the node with the given key from the hash table. If the 
   key does not exist, nothing will be changed. Else, numElements will be 
   decremented.  */
template<typename Key, typename Value>
void HashTable<Key, Value>::remove(Key k) {

    // If key exists and the associated node is removed
    if (buckets[hash(k)]->remove(k)) { 
        numElements--;
    }
}

/* Returns the hashed index given the key. Hash the string of the key. */
template<typename Key, typename Value>
size_t HashTable<Key, Value>::hash(Key k) const {
    return hashFunction(toString(k)) % numBuckets;
}
/* Converts the given key to a string */
template<typename Key, typename Value>
std::string HashTable<Key, Value>::toString(Key k) const {
    std::ostringstream oss;
    oss << k;
    return oss.str();
}



#endif