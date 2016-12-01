/* 
   SetNode.h
   Header and implementations of the nodes of the container Set, an ordered 
   collection of unique elements.

   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* This is designed to be used in conjunction with the LinkedList. Therefore, 
   everything is made private. This is made into a class instead of a struct
   because it should have the ability to store any object, including those 
   that needs to be initialized. 

   Because the implementation of the constructor is so short and concise, 
   I chose to implement directly in the class definition. */
/*****************************************************************************/
/*                         Header and Implementaions                         */
/*****************************************************************************/
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
        ListNode(const Key &k, const Value &v) : key(k), 
                                                 val(v), 
                                                 next(nullptr) { }
};
#endif