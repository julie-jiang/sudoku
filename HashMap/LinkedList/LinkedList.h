/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "ListNode.h"
#include "ListIterator.h"
template<typename Key, typename Value>
class LinkedList {
    public:
        typedef ListIterator<Key, Value> iterator;
        LinkedList(); 
        ~LinkedList(); 
        bool empty();
        size_t size(); 
        Value &operator[](const Key &);
        bool insert(Key, Value);
        bool remove(Key);
        iterator begin(); 
        iterator end();
    private:
        ListNode<Key, Value> *front;
};
/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/
template<typename Key, typename Value>
LinkedList<Key, Value>::LinkedList() 
{
    front = nullptr;    
}

template<typename Key, typename Value>
LinkedList<Key, Value>::~LinkedList() 
{
    
    ListNode<Key, Value> *current = front;
    while (current != nullptr) {
        ListNode<Key, Value> *temp = current;
        current = current->next;
        delete temp;
    }
    
}
template<typename Key, typename Value>
ListIterator<Key, Value> LinkedList<Key, Value>::begin() 
{
    return ListIterator<Key, Value>(front);
}
template<typename Key, typename Value>
ListIterator<Key, Value> LinkedList<Key, Value>::end() 
{
    return ListIterator<Key, Value>(nullptr);
}

template<typename Key, typename Value>
bool LinkedList<Key, Value>::empty()
{
    return (front == nullptr);
}
template<typename Key, typename Value>
size_t LinkedList<Key, Value>::size() 
{
    size_t num_nodes = 0;
    ListNode<Key, Value> *current = front;
    
    while (current != nullptr) { 
        current = current->next;
        num_nodes++;
    }

    return num_nodes;
}


template<typename Key, typename Value>
Value &LinkedList<Key, Value>::operator[](const Key &k)
{
    ListNode<Key, Value> *current = front;
    while (current != nullptr) {
        if (current->key == k) {
            return current->val;
        }
        current = current->next;
    }
    throw std::logic_error("Value does not exist");

}


template<typename Key, typename Value>
bool LinkedList<Key, Value>::insert(Key k, Value v)
{
    ListNode<Key, Value> *newNode = new ListNode<Key, Value>(k, v);
    if (empty()) {
        front = newNode;
    } else {
        ListNode<Key, Value> *current = front;
        ListNode<Key, Value> *previous;
        while (current != nullptr) {
            if (current->key == k) {
                current->val = v;
                delete newNode;
                return false;
            }
            previous = current;
            current = current->next;
        }
        previous->next = newNode;
    }
    return true;
}

template<typename Key, typename Value>
bool LinkedList<Key, Value>::remove(Key k)
{
    ListNode<Key, Value> *current = front;
    ListNode<Key, Value> *previous = nullptr;
    while (current != nullptr) {
        if (current->key == k) {
            if (previous != nullptr)
                previous->next = current->next;
            else 
                front = current->next;
            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;

}




#endif

