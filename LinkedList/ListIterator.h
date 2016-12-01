/* 
   ListIterator.h
   Header and implementations of the iterator of the container LinkedList.

   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* This is designed to be used in conjunction with the LinkedList. A LinkedList
   is iterated by following the pointers stored in the nodes (see ListNode) 
   until it reaches the end. Because the implementaions are very short, I chose
   to implement directly in the class definition.                            */
/*****************************************************************************/
/*                         Header and Implementaions                         */
/*****************************************************************************/
#ifndef LISTITERATOR_H
#define LISTITERATOR_H
template<typename Key, typename Value> class HTIterator;
template<typename Key, typename Value>
class ListIterator
{
    public:
        friend class LinkedList<Key, Value>;
        friend class HTIterator<Key, Value>;
        ListIterator(): iter_node(nullptr) {}

        ListIterator &operator++() {                  // Increment operator
            iter_node = iter_node->next;
            return *this;
        }
        bool operator==(const ListIterator &source) { // Comparison operators
            return (iter_node == source.iter_node);
        }

        bool operator!=(const ListIterator &source) {
            return (iter_node != source.iter_node);
        }

        Key   key()   { return iter_node->key;}       // Returns the key 

        Value value() { return iter_node->val;}       // Returns the value

    private:
        ListNode<Key, Value> *iter_node;
        ListIterator(ListNode<Key, Value> *node) : iter_node(node) {}
};

#endif