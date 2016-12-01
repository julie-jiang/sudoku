/* 
   HTIterator.h
   Header and implementations of the iterator of the container HashTable.

   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* This is designed to be used in conjunction with the HashTable. Some of the 
   short oneliner functions are implemented directly in the class definition.
   Others are implemented below the class definition. 
   Since the hash table is a bunch of LinkedLists, this iterator utilizes the 
   LinkedList iterator to traverse the nodes. The order of traversal is 
   first determined by the index that each node is hashed into, and then 
   determined by the order of insertion (since each LinkedList is iterated 
   in order of insertion).                                                   */
#ifndef HTIterator_H
#define HTIterator_H
/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/
template<typename Key, typename Value> class HashTable;
template<typename Key, typename Value>
class HTIterator {
    public:
        friend class HashTable<Key, Value>;
        // Comparison operators
        bool operator==(const HTIterator &source) { return (it == source.it);}
        bool operator!=(const HTIterator &source) { return (it != source.it);}
        
        // Return key or value stored in this node
        Key    key()   { return it.key(); }
        Value  value() { return it.value(); }

        HTIterator &operator++();

    private:
        typename LinkedList<Key, Value>::iterator it; 
        LinkedList<Key, Value> **buckets;
        size_t bucketIndex; 
        size_t num_buckets;
        HTIterator(LinkedList<Key, Value> **buckets, int size);
        void find_next_bucket();
        
};
/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/
/* Constructor. If buckets is not nullptr, set iterator to the first node 
   in buckets. If buckets is empty or if buckets is nullptr, then set iterator
   to nullptr. */
template<typename Key, typename Value>
HTIterator<Key, Value>::HTIterator(LinkedList<Key, Value> **buckets, 
                                   int size) {
    this->buckets = buckets;
    num_buckets = size;
    it = nullptr;
    if (buckets != nullptr) {
        bucketIndex = 0;
        find_next_bucket();
    }
}
/* Overloads increment operator. If the iterator is at the end of the 
   current index, set iterator to the next nonempty bucket or nullptr */
template<typename Key, typename Value>
HTIterator<Key, Value> &HTIterator<Key, Value>::operator++() {
    ++it;
    if (it == buckets[bucketIndex]->end()) {
        bucketIndex++;
        find_next_bucket();
    } 
    return *this;
}
/* Beginning from the current bucketIndex, find the index of the next 
   nonempty bucket and set iterator to the beginning of the linkedlist at
   that bucket. If no nonempty bucket can be found, set iterator to nullptr */
template<typename Key, typename Value>
void HTIterator<Key, Value>::find_next_bucket() {
    // Loop until either the end of buckets is reached 
    // or if a bucket is not empty. 
    while(bucketIndex < num_buckets and buckets[bucketIndex]->empty()) {
        bucketIndex++;
    } 
    // If no nonempty buckets are found, set iterator to nullptr. 
    // Otherwise, set iterator to the first element in the bucket
    it = (bucketIndex == num_buckets) ? nullptr:buckets[bucketIndex]->begin();
}
#endif