#ifndef LISTNODE_H
#define LISTNODE_H

template<typename Key, typename Value> class LinkedList;
template<typename Key, typename Value> class ListIterator;
template<typename Key, typename Value> 

class ListNode 
{

	friend class LinkedList<Key, Value>;
	friend class ListIterator<Key, Value>;

    private:
        Key   key;
        Value val;
        ListNode<Key, Value> *next;
        ListNode(const Key &k, const Value &v) : key(k), val(v), next(nullptr) { }
};
#endif