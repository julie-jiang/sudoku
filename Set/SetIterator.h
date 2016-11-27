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
        SetIterator();
        ~SetIterator();
        SetNode<T> *operator++();
        bool operator!=(const SetIterator &);
        bool operator==(const SetIterator &);
        T &operator*();

    private:
        SetNode<T> *iter_node;
        std::stack<SetNode<T>*> elements;
        SetIterator(SetNode<T> *);
        void traversal(SetNode<T> *);
}; 
/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/
template<typename T>
SetIterator<T>::SetIterator(): iter_node(0)
{

}
template<typename T>
SetIterator<T>::~SetIterator()
{

}
template<typename T>
SetIterator<T>::SetIterator(SetNode<T> *node): iter_node(node)
{
     if (node != nullptr) {
        traversal(node);
        iter_node = elements.top();
        elements.pop();
    } else {
        iter_node = nullptr;
    }
}
template<typename T>
void SetIterator<T>::traversal(SetNode<T> *node)
{
    if (node->left != nullptr) {
        traversal(node->left);
    }
    elements.push(node);

    if (node->right != nullptr) {
        traversal(node->right);
    }
}
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
template<typename T>
bool SetIterator<T>::operator!=(const SetIterator &source) 
{
    return (iter_node != source.iter_node);
}
template<typename T>
bool SetIterator<T>::operator==(const SetIterator &source) 
{
    return (iter_node == source.iter_node);
}
template<typename T>
T &SetIterator<T>::operator*() 
{
    return iter_node->value;
}

#endif