#ifndef MAPITERATOR_H
#define MAPITERATOR_H
/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/
template<typename Key, typename Value> class HashMap;
template<typename Key, typename Value>
class MapIterator {
    public:
        friend class HashMap<Key, Value>;
        MapIterator &operator++();
        // Simple straight forward functions 
        bool operator==(const MapIterator &source) { return (it == source.it);}
        bool operator!=(const MapIterator &source) { return (it != source.it);}
        Key   key()   { return it.key(); }
        Value value() { return it.value(); }

    private:
        typename LinkedList<Key, Value>::iterator it;
        LinkedList<Key, Value> **buckets;
        size_t bucketIndex;
        size_t num_buckets;
        MapIterator(LinkedList<Key, Value> **buckets, int size);
        
};
/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/
template<typename Key, typename Value>
MapIterator<Key, Value>::MapIterator(LinkedList<Key, Value> **buckets, int size)
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
MapIterator<Key, Value> &MapIterator<Key, Value>::operator++()
{
    ++it;
    if (it == buckets[bucketIndex]->end()) {
        bucketIndex++;
        while(bucketIndex < num_buckets and buckets[bucketIndex]->empty()) {
            bucketIndex++;
        } 
        (bucketIndex == num_buckets) ? 
        it = nullptr: it = buckets[bucketIndex]->begin();
    } 
    return *this;

}
#endif