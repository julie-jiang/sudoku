#ifndef NODE_H
#define NODE_H

template<typename Key, typename Value> class LinkedList;
template<typename Key, typename Value> class Iterator;
template<typename Key, typename Value> 
class Node {
	friend class LinkedList<Key, Value>;
	friend class Iterator<Key, Value>;
    private:
        Key   key;
        Value val;
        Node<Key, Value> *next;
        Node(const Key &k, const Value &v) : key(k), val(v), next(nullptr) { }
};
#endif