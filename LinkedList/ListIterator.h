#ifndef LISTITERATOR_H
#define LISTITERATOR_H
template<typename Key, typename Value>
class ListIterator
{
    public:
        friend class LinkedList<Key, Value>;
        ListIterator() : iter_node(0) {}

        ListIterator &operator ++() {
            iter_node = iter_node->next;
            return *this;
        }
        bool operator==(const ListIterator &source) {
            return (iter_node == source.iter_node);

        }

        bool operator!=(const ListIterator &source) {
            return (iter_node != source.iter_node);
        }

        Key key() { 
            return iter_node->key;
        }

        Value value() {
            return iter_node->val;
        }

    private:
        ListNode<Key, Value> *iter_node;
        ListIterator(ListNode<Key, Value> *node) : iter_node(node) {}
};

#endif