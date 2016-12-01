/* 
   LinkedList.h
   Header and implementations of the container LinkedList, a linear data 
   structure. This LinkedList is designed to be used for the Hash Table, so
   it every node in this LinkedList consists of a key and a value.
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* A LinkedList object can be created with the default constructor. Once 
   created, you can
      (1) insert a key, value pair into the list
      (2) query for the value with a key using subscript operator
      (3) remove a key (and accordingly its value) from the list
      (4) get the size of the linkedlist
      (5) check if the list is empty
      (6) iterate through the list in order of insertion

   Because this is the container used in the HashTable, keys are immutable,
   meaning they cannot be changed. Values, however, can be overwritten.

   For more usage information and examples, please see the README.md in this 
   directory. 
*/
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
        LinkedList(); 
        ~LinkedList(); 
        bool     insert(Key, Value);
        Value   &operator[](const Key &);
        bool     remove(Key);
        bool     empty();
        size_t   size(); 
        typedef ListIterator<Key, Value> iterator;
        iterator begin(); 
        iterator end();
    private:
        ListNode<Key, Value> *front;
};
/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/

/* Constructor */
template<typename Key, typename Value>
LinkedList<Key, Value>::LinkedList() {
    front = nullptr;    
}
/* Destructor */
template<typename Key, typename Value>
LinkedList<Key, Value>::~LinkedList() {
    ListNode<Key, Value> *current = front;
    while (current != nullptr) {
        ListNode<Key, Value> *temp = current;
        current = current->next;
        delete temp;
        temp = nullptr;
    }
}

/* Insert a key, value pair to the linkedlist. Returns false if key already
   exists, in which case the old value will be overwritten with the new one. */
template<typename Key, typename Value>
bool LinkedList<Key, Value>::insert(Key k, Value v) {
    ListNode<Key, Value> *newNode = new ListNode<Key, Value>(k, v);
    if (empty()) {
        front = newNode;
    } else {
        ListNode<Key, Value> *current = front;
        ListNode<Key, Value> *previous;
        // Loop until we've reached the end of the list or until the key
        // is found
        while (current != nullptr) {
            if (current->key == k) {
                current->val = v;
                delete newNode;
                return false;
            }
            previous = current;  
            current = current->next;
        }
        previous->next = newNode; // Link new node 
    }
    return true;
}

/* Removes the node with the given key from the list. Returns true if the key
   found and removed. Returns false if the key is not found. */
template<typename Key, typename Value>
bool LinkedList<Key, Value>::remove(Key k) {
    ListNode<Key, Value> *current = front;
    ListNode<Key, Value> *previous = nullptr;
    while (current != nullptr) {

        // Remove the node and bridge the gap
        if (current->key == k) {
            (previous != nullptr) ? previous->next = current->next : 
                                    front = current->next;
            delete current;
            return true;
        }
        previous = current;   
        current = current->next;
    }
    return false; // Key not found
}

/* Returns a referece of the associated value of the key. Throws logic_error
   if the key does not exist. */
template<typename Key, typename Value>
Value &LinkedList<Key, Value>::operator[](const Key &k) {
    ListNode<Key, Value> *current = front;
    while (current != nullptr) {
        if (current->key == k) {
            return current->val;
        }
        current = current->next;
    }
    throw std::logic_error("Value does not exist");
}

/* Returns true if the list is empty */
template<typename Key, typename Value>
bool LinkedList<Key, Value>::empty() {
    return (front == nullptr);
}
/* Returns the number of nodes stored in the list */
template<typename Key, typename Value>
size_t LinkedList<Key, Value>::size() {
    size_t num_nodes = 0;
    ListNode<Key, Value> *current = front;
    
    while (current != nullptr) { 
        current = current->next;
        num_nodes++;
    }
    return num_nodes;
}

/* Returns an interator object that points to the first node in the list */
template<typename Key, typename Value>
ListIterator<Key, Value> LinkedList<Key, Value>::begin() {
    return ListIterator<Key, Value>(front);
}

/* Returns an interator object that points to nullptr, which serves as a 
   sentinel for the end of the list */
template<typename Key, typename Value>
ListIterator<Key, Value> LinkedList<Key, Value>::end() {
    return ListIterator<Key, Value>(nullptr);
}


#endif

