#ifndef ITERATOR_H
#define ITERATOR_H
#include <iterator>
template<typename Key, typename Value>
class Iterator : public std::iterator<std::forward_iterator_tag, Node<Key, Value>>{
    private:
        Iterator(Node<Key, Value>* node) : iter_node(node) {}

    public:
        friend class LinkedList<Key, Value>;
        Iterator() : iter_node(0) {}

        Iterator& operator ++() {
            iter_node = iter_node->next;
            return *this;
        }
        bool operator==(const Iterator &source) {
            return (iter_node == source.iter_node);

        }

        bool operator!=(const Iterator &source) {
            return (iter_node != source.iter_node);

        }

        Key key() {
            return iter_node->key;

        }
        Value value() {
            return iter_node->val;
        }

    private:
        Node<Key, Value> * iter_node;
};

#endif