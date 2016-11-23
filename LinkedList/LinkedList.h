
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/
#include "Node.h"
#include "Iterator.h"
template<typename Key, typename Value>
class LinkedList {
    public:
        typedef Iterator<Key, Value> iterator;
    public:
        LinkedList(); 
        ~LinkedList(); /* Destructor */
        bool empty();
        int size(); 
        Value get(Key);
        Value &operator[](const Key);
        void insert(Key, Value);
        void remove(Key);
        iterator begin() {
            return Iterator<Key, Value>(front);
        }
        iterator end() {
            return Iterator<Key, Value>(nullptr);
        }
    private:
        Node<Key, Value> *front;
        Node<Key, Value> *lastNode();
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
    
    Node<Key, Value> *current = front;
    while (current != nullptr) {
        Node<Key, Value> *temp = current;
        current = current->next;
        delete temp;
    }
    
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
    Node<Key, Value> *current = front;
    
    while (current != nullptr) { 
        current = current->next;
        num_nodes++;
    }

    return num_nodes;
}

 // assumes non empty!!!!!
template<typename Key, typename Value>
Node<Key, Value> *LinkedList<Key, Value>::lastNode()
{
    Node<Key, Value> *current = front;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;

}
template<typename Key, typename Value>
Value LinkedList<Key, Value>::get(Key k)
{
    Node<Key, Value> *current = front;
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
    /*
    Node<Key, Value> *current = front;
    while (current != nullptr) {
        if (current->key == k) {
            return current->val;
        }
        current = current->next;
    }*/
    Node<Key, Value> *current = front;
    while (current->key != k) {
        current = current->next;
    }
    return current->val;

}

template<typename Key, typename Value>
void LinkedList<Key, Value>::insert(Key k, Value v)
{
    Node<Key, Value> *newNode = new Node<Key, Value>(k, v);
    if (empty()) {
        front = newNode;
    } else {
        Node<Key, Value> *current = lastNode();
        current->next = newNode;
    }
}
template<typename Key, typename Value>
void LinkedList<Key, Value>::remove(Key k)
{
    Node<Key, Value> *current = front;
    if (not empty()) {  
        while (current->next != nullptr) {
            if (current->next->key == k) {
                Node<Key, Value> *temp= current->next;
                current->next = current->next->next;
                delete temp;

            }
        }
    }
}



#endif

