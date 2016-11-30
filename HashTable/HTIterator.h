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
        HTIterator &operator++();
        // Simple straight forward functions 
        bool operator==(const HTIterator &source) { return (it == source.it);}
        bool operator!=(const HTIterator &source) { return (it != source.it);}
        Key   key()   { return it.key(); }
        Value value() { return it.value(); }

    private:
        typename LinkedList<Key, Value>::iterator it;
        LinkedList<Key, Value> **buckets;
        size_t bucketIndex;
        size_t num_buckets;
        HTIterator(LinkedList<Key, Value> **buckets, int size);
        
};
/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/
template<typename Key, typename Value>
HTIterator<Key, Value>::HTIterator(LinkedList<Key, Value> **buckets, int size)
{
    this->buckets = buckets;
    num_buckets = size;
    it = nullptr;
    if (buckets != nullptr) {
        bucketIndex = 0;
        while (bucketIndex < num_buckets and buckets[bucketIndex]->empty()){
            bucketIndex++;
        }
        if (bucketIndex < num_buckets) {
            it = buckets[bucketIndex]->begin();
        }
    }
}
template<typename Key, typename Value>
HTIterator<Key, Value> &HTIterator<Key, Value>::operator++()
{
    ++it;
    if (it == buckets[bucketIndex]->end()) {
        bucketIndex++;
        while(bucketIndex < num_buckets and buckets[bucketIndex]->empty()) {
            bucketIndex++;
        } 
        it = (bucketIndex == num_buckets) ? 
              nullptr : buckets[bucketIndex]->begin();
    } 
    return *this;

}
#endif