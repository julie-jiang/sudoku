#ifndef MAPITERATOR_H
#define MAPITERATOR_H
template<typename Key, typename Value> class HashMap;
template<typename Key, typename Value>
class MapIterator {
	public:
		friend class HashMap<Key, Value>;
		MapIterator &operator++() {
			++it;
			if (*it == buckets[bucketIndex]->end()) {
				bucketIndex++;
				while(bucketIndex < bucketSize and buckets[bucketIndex]->empty()) {
					bucketIndex++;
				} 
				if (bucketIndex == bucketSize) {
					std::cout << "iterator at end!\n";
					it = nullptr;
				} else {
					std::cout << "iterator at index " << bucketIndex;
					std::cout << ". Key = " << it->key() << std::endl;
					*it = buckets[bucketIndex]->begin();
				}
			} else {
				std::cout << "iterator at index " << bucketIndex;
				std::cout << ". Key = " << (*it).key() << "!" << std::endl;
			}
			return *this;

		}
		bool operator==(const MapIterator &source) {
			return (it == source.it);
		}
		bool operator!=(const MapIterator &source) {
			return (it != source.it);
		}
		Key key() {
			return it->key();
		}

	private:
		typename LinkedList<Key, Value>::iterator *it;
		LinkedList<Key, Value> **buckets;
		size_t bucketIndex;
		size_t bucketSize;
		MapIterator(LinkedList<Key, Value> **buckets, int size) {
			this->buckets = buckets;
			bucketSize = size;
			if (buckets != nullptr) {
	 			bucketIndex = 0;
				while (bucketIndex < bucketSize and buckets[bucketIndex]->empty()) {
					bucketIndex++;
				}
				if (bucketIndex == bucketSize) {
					it = nullptr;
				} else {
					std::cout << "iterator at index " << bucketIndex;
					std::cout << ". Key = " << (*it).key() << "!" << std::endl;
					*it = buckets[bucketIndex]->begin();
				}
			} else {
				it = nullptr;
			}

		}
};
#endif