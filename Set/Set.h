#ifndef SET_H
#define SET_H
#include <iostream>
#include <sstream>
#include "SetNode.h"
#include "SetIterator.h"
/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/
template<typename T>
class Set;
template<typename T>
std::ostream &operator <<(std::ostream &, const Set<T> &);

template<typename T>
class Set {
    public:
        typedef SetIterator<T> iterator;
        Set();
        ~Set();
        Set(const Set &);
        void add(T);
        bool contains(T);
        T pop();
        void remove(T);
        bool empty();
        size_t size();
        friend std::ostream &operator << <>(std::ostream &, const Set &);
        void printTree();
        T top();
        iterator begin() const;
        iterator end() const;
    private:
        SetNode<T> *root;
        SetNode<T> *add(SetNode<T> *, T);
        bool contains(SetNode<T> *, T);
        SetNode<T> *remove(SetNode<T> *, T);
        void toString(SetNode<T> *, std::string &) const;
        std::string value2string(T &) const;
        void printTree(SetNode<T> *);
        size_t size(SetNode<T> *, int);
        
        int getBalance(SetNode<T> *);
        int height(SetNode<T> *);
        int max(int, int);
        SetNode<T> *getMinSetNode(SetNode<T> *);
        SetNode<T> *rotateRight(SetNode<T> *);
        SetNode<T> *rotateLeft(SetNode<T> *);
        SetNode<T> *removeSetNode(SetNode<T> *);
        SetNode<T> *updateHeight(SetNode<T> *);
        
        
};

/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/

template<typename T>
Set<T>::Set()
{
    root = nullptr;
}


template<typename T>
Set<T>::~Set()
{

}
template<typename T>
Set<T>::Set(const Set &source)
{
    root = nullptr;
    for (Set<T>::iterator i = source.begin(); i != source.end(); ++i) {
        add(*i);
    }

}
template<typename T>
SetIterator<T> Set<T>::begin() const
{
    return SetIterator<T>(root);
}
template<typename T>
SetIterator<T> Set<T>::end() const
{
    return SetIterator<T>(nullptr);
}
template<typename T>
bool Set<T>::contains(T val)
{
    if (not empty())
        return contains(root, val);
    return false;

}
template<typename T>
bool Set<T>::contains(SetNode<T> *node, T val)
{
    // If SetNode == s, return true
    if (node->value == val) {
        return true;
    } 

    // Search left subtree if SetNode > s
    if (node->value > val and node->left != nullptr) {
        return contains(node->left, val);
    }

    // Search right subtree if SetNode < s
    else if (node->right != nullptr) {
        return contains(node->right, val);
    } 

    // s does not exist in BST. Return false
    else {
        return false;
    }
}

template<typename T>
bool Set<T>::empty()
{
    return (root == nullptr);
}
template<typename T>
void Set<T>::add(T val)
{
    root = add(root, val);
        
}


template<typename T>
SetNode<T> *Set<T>::add(SetNode<T> *node, T val)
{
    // Make new SetNode 
    if (node == nullptr) {
        node = new SetNode<T>(val);

    // Insert left if currSetNode is greater than newSetNode
    } else if (node->value > val) {
        node->left = add(node->left, val);

    // Insert right if SetNode is smaller than s
    } else  if (node->value < val) {
        node->right = add(node->right, val);
    }
    
    // Update height
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);
    
    if (balance > 1) {
        // Right right unbalance 
        if (val > node->right->value) {    
            return rotateLeft(node);
        // Right left unbalance
        } else { // val < SetNode->right->value              
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    } else if (balance < -1) {
        // Left left unbalance
        if (val < node->left->value) {
            return rotateRight(node);
        // Left right unbalance
        } else { // val > SetNode->left->value
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    return node;
}
template<typename T>
T Set<T>::pop()
{
    T value = root->value;
    remove(value);
    return value;
}

template<typename T>
void Set<T>::remove(T val)
{
    root = remove(root, val);
}


template<typename T>
SetNode<T> *Set<T>::remove(SetNode<T> *node, T val)
{   
    // Standard BST removal 
    if (node == nullptr) 
        return node;
   
   // If SetNode == val, remove SetNode    
    if (val == node->value) 
        node = removeSetNode(node); 

    // Search left subtree if SetNode > s  
    else if (val < node->value)
        node->left = remove(node->left, val);
        

    // Search right subtree if SetNode < s
    else 
        node->right = remove(node->right, val);  

    if (node == nullptr) 
        return node;
    
    // Update height
    node = updateHeight(node);

    return node;
}

template<typename T>
SetNode<T> *Set<T>::updateHeight(SetNode<T> *node)
{
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);
        
    if (balance > 1) {
        // Right right unbalance   
        if (getBalance(root->right) >= 0) {   
            return rotateLeft(node);

        // Right left unbalance 
        } else {            
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    } else if (balance < -1) {
        // Left left unbalance
        if (getBalance(root->left) <= 0) { 
            return rotateRight(node);

        // Right left unbalance
        } else { 
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    return node;
}
template<typename T>
SetNode<T> *Set<T>::removeSetNode(SetNode<T> *node)
{
    // If SetNode has two children, find its in-order successor and replace SetNode 
    // with it. Then delete an instance of its in-order successor through 
    // recursion
    if (node->left != nullptr and node->right != nullptr) {
        SetNode<T> *successor = getMinSetNode(node->right);
        node->value  = successor->value;
        node->right  = remove(node->right, successor->value);
    
    // Else if SetNode has only one or no child.
    } else {
        SetNode<T> *temp = node->left ? node->left : node->right;

        // If SetNode has no child
        if (temp == nullptr) {
            temp = node;
            node = nullptr;
        } else {
            *node = *temp;
        }
        delete temp;
    }

    return node;
}
template<typename T>
SetNode<T> *Set<T>::getMinSetNode(SetNode<T> *node)
{
    // Keep traversing left until end of AVL tree is reached
    if (node->left != nullptr) {
        return getMinSetNode(node->left);
    }
    return node;
}


template<typename T>
SetNode<T> *Set<T>::rotateLeft(SetNode<T> *node)
{
    SetNode<T> *rightChild     = node->right;
    SetNode<T> *rightLeftChild = rightChild->left;

    rightChild->left = node;
    node->right      = rightLeftChild;

    node->height       = max(height(node->left), height(node->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
    
    return rightChild;
}
template<typename T>
SetNode<T> *Set<T>::rotateRight(SetNode<T> *node)
{
    SetNode<T> *leftChild      = node->left;
    SetNode<T> *leftRightChild = leftChild->right;

    leftChild->right = node;
    node->left       = leftRightChild;

    node->height      = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;
    return leftChild;

}

template<typename T>
int Set<T>::getBalance(SetNode<T> *node)
{
    return (height(node->right) - height(node->left));
}

template<typename T>
int Set<T>::height(SetNode<T> *node)
{
    if (node != nullptr)
        return node->height;
    return 0;
}

template<typename T>
int Set<T>::max(int a, int b)
{
    return (a > b) ? a : b;
}

template<typename T>
std::ostream &operator<<(std::ostream &output, const Set<T> &source)
{
    std::string str = "[";
    source.toString(source.root, str);
    str.erase(str.size() - 2);
    str += "]";
    output << str;
    return output;
}
template<typename T>
void Set<T>::toString(SetNode<T> *node, std::string &str) const
{
    if (node->left != nullptr) 
        toString(node->left, str);
    
    str += (value2string(node->value) + ", ");

    if (node->right != nullptr) 
        toString(node->right, str);
}
template<typename T>
std::string Set<T>::value2string(T &v) const
{
    std::string result;
    std::ostringstream oss;
    oss << v;
    return oss.str();
}
template<typename T>
void Set<T>::printTree()
{
    std::cout << "[";
    if (not empty()) {
        printTree(root);
    }
    std::cout << "]" << std::endl;
}
template<typename T>
void Set<T>::printTree(SetNode<T> *node)
{
    // Traverse left subtree 
    std::cout << "[";
    if (node->left != nullptr) {    
        printTree(node->left);  
    } 
    // Print current SetNode
    std::cout << "] " << node->value << " [";
    
    // Traverse right subtree
    if (node->right != nullptr) {
        printTree(node->right);
    }
    std::cout << "]";
    
}
template<typename T>
size_t Set<T>::size()
{
    return size(root, 0);
}
template<typename T>
size_t Set<T>::size(SetNode<T> *node, int sum)
{
    if (node != nullptr) {
        sum++;
        // Traverse left subtree 
        sum = size(node->left, sum);
        // Traverse right subtree
        sum = size(node->right, sum);
    }
    return sum;
}
template<typename T>
T Set<T>::top()
{
    return root->value;
}
#endif