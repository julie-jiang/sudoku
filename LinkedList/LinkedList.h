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
        int size(); 
        Value get(Key);
        Value &operator[](const Key);
        void insert(Key, Value);
        void remove(Key);
        iterator begin(); 
        iterator end();
    private:
        ListNode<Key, Value> *front;
        ListNode<Key, Value> *lastNode();
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
int LinkedList<Key, Value>::size() 
{
    int num_nodes = 0;
    ListNode<Key, Value> *current = front;
    
    while (current != nullptr) { 
        current = current->next;
        num_nodes++;
    }

    return num_nodes;
}

 // assumes non empty!!!!!
template<typename Key, typename Value>
ListNode<Key, Value> *LinkedList<Key, Value>::lastNode()
{
    ListNode<Key, Value> *current = front;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;

}
template<typename Key, typename Value>
Value LinkedList<Key, Value>::get(Key k)
{
    ListNode<Key, Value> *current = front;
    while (current != nullptr) {
        if (current->key == k) {
            return current->val;
        }
        current = current->next;
    }
    return 0;
}
template<typename Key, typename Value>
Value &LinkedList<Key, Value>::operator[](const Key k)
{
    ListNode<Key, Value> *current = front;
    while (current->key != k) {
        current = current->next;
    }
    return current->val;

}

template<typename Key, typename Value>
void LinkedList<Key, Value>::insert(Key k, Value v)
{
    ListNode<Key, Value> *newNode = new ListNode<Key, Value>(k, v);
    if (empty()) {
        front = newNode;
    } else {
        ListNode<Key, Value> *current = lastNode();
        current->next = newNode;
    }
}
template<typename Key, typename Value>
void LinkedList<Key, Value>::remove(Key k)
{
    ListNode<Key, Value> *current = front;
    if (not empty()) {  
        while (current->next != nullptr) {
            if (current->next->key == k) {
                ListNode<Key, Value> *temp= current->next;
                current->next = current->next->next;
                delete temp;

            }
        }
    }
}



#endif

