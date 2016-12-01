/* 
   SetIterator.h
   Header and implementations for the iterator of the container Set, an ordered
   collection of unique elements. 

   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* This is designed to be used in conjunction with the Set. Therefore, the 
   constructor is made private. To iterate through a Set, it first pushes all
   the elements in the Set to a stack via in-order traversal. Then it pops
   the elements in the stack one-by-one. */
#ifndef SETITERATOR_H
#define SETITERATOR_H
#include <cstdlib>
#include <stack>
/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/

template<typename T>
class SetIterator 
{
    public:
        friend class Set<T>;
        SetNode<T> *operator++();
        bool operator!=(const SetIterator &);
        bool operator==(const SetIterator &);
        T &operator*();

    private:
        SetNode<T> *iter_node;
        std::stack<SetNode<T>*> elements;
        SetIterator(SetNode<T> *);
        void traverse(SetNode<T> *);
}; 
/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/
/* Constructor. If the node is not nullptr, traverse the tree beginning from 
   that node and pushes all nodes to elements (a stack), then set iter_node 
   to the first node in the stack. Else, iter_node is nullptr, which acts as a 
   sentinel. */
template<typename T>
SetIterator<T>::SetIterator(SetNode<T> *node): iter_node(node)
{
    if (node != nullptr) {
        traverse(node);
        iter_node = elements.top();
        elements.pop();
    } else {
        iter_node = nullptr;
    }
}
/* Recursively traverses the tree starting from the given node via in-order
   traversal. Pushes everything to elements (a stack) */ 
template<typename T>
void SetIterator<T>::traverse(SetNode<T> *node)
{
    if (node->left != nullptr) {
        traverse(node->left);
    }
    elements.push(node);

    if (node->right != nullptr) {
        traverse(node->right);
    }
}
/* Overload the "++" operator. Returns next node in elements if elements
   is not empty. Else returns nullptr */
template<typename T>
SetNode<T> *SetIterator<T>::operator++()
{
    if (elements.empty()) {
        iter_node = nullptr;
    } else {
        iter_node = elements.top();
        elements.pop();
    }
    return iter_node;
}
/* Overload the "!=" operator. Returns true if they don't equal*/
template<typename T>
bool SetIterator<T>::operator!=(const SetIterator &source) 
{
    return (iter_node != source.iter_node);
}
/* Overload the "==" operator. Returns true if they do equal */
template<typename T>
bool SetIterator<T>::operator==(const SetIterator &source) 
{
    return (iter_node == source.iter_node);
}
/* Overload the dereferencing operator "*". Returns the value stored
   in this node */
template<typename T>
T &SetIterator<T>::operator*() 
{
    return iter_node->value;
}


#endif