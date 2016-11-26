#ifndef SetIterator_H
#define SetIterator_H
#include <cstdlib>
#include <stack>
template<typename T>
class SetIterator 
{
    public:
        friend class Set<T>;
        SetIterator() : iter_node(0) {}

        SetIterator &operator++() {
            *iter_node = elements.top();
            elements.pop();
            return iter_node;
        }
        bool operator!=(const SetIterator &source) {
            return (iter_node != source.iter_node);
        }
        bool operator==(const SetIterator &source) {
            return (iter_node == source.iter_node);
        }

        T &operator*() const {
            return iter_node->value;
        }

    private:
        SetNode<T> *root;
        SetNode<T> *iter_node;
        std::stack<SetNode<T>> elements;
        SetIterator(SetNode<T> *node) : iter_node(node) 
        {
            if (node != nullptr)
                treeTraversal(node);
        }
        
        void traversal(SetNode<T> *node) 
        {
            if (node->left != nullptr) {
                traversal(node->left);
            }
            elements.push(node);

            if (node->right != nullptr) {
                traversal(node->right);
            }

        }
}; 

#endif