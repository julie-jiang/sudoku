/* 
   SetNode.h
   Header and implementations for the nodes of the container Set, an ordered 
   collection of unique elements.

   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* This is designed to be used in conjunction with the Set. Therefore, the 
   Everything is made private. This is made into a class instead of a struct
   because it should have the ability to store any object, including those 
   that needs to be initialized. 

   Because the implementation of the constructor is so short and concise, 
   there is no separate implementation. */

#ifndef SETNODE_H
#define SETNODE_H
template<typename T> class Set;
template<typename T> class SetIterator;
template<typename T>
class SetNode 
{
    friend class Set<T>;
    friend class SetIterator<T>;

    private:
        int height;
        T value;
        SetNode<T> *left;
        SetNode<T> *right;
        SetNode(const T &val) : height(1), 
                                value(val), 
                                left(nullptr), 
                                right(nullptr) { }
};
#endif