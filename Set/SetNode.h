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
        SetNode(const T &val) : height(1), value(val), left(nullptr), right(nullptr) { }
};
#endif