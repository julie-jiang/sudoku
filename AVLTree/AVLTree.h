/*
 * Easy to add element 
 * Easy to remove element
 * Easy to find element
 */

/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/

#ifndef AVLTREE_H
#define AVLTREE_H
#include <cstdlib>
#include <stack>
#include "TreeNode.h"

template<typename ElemType>


class AVLTree {
    public:
        AVLTree();
        ~AVLTree();
        void add(ElemType);
        bool contains(ElemType);
        ElemType pop();
        void remove(ElemType);
        bool empty();
        int size();
        void print();
        void printTree();
        ElemType getRoot();
        std::stack<ElemType> getElements();
    private:
        TreeNode<ElemType> *root;

        TreeNode<ElemType> *add(TreeNode<ElemType> *, ElemType);
        bool contains(TreeNode<ElemType> *, ElemType);
        TreeNode<ElemType> *remove(TreeNode<ElemType> *, ElemType);
        void print(TreeNode<ElemType> *);
        void printTree(TreeNode<ElemType> *);
        void getElements(TreeNode<ElemType> *, std::stack<ElemType> &);
        int size(TreeNode<ElemType> *, int);
        
        int getBalance(TreeNode<ElemType> *);
        int height(TreeNode<ElemType> *);
        int max(int, int);
        TreeNode<ElemType> *getMinTreeNode(TreeNode<ElemType> *);
        TreeNode<ElemType> *rotateRight(TreeNode<ElemType> *);
        TreeNode<ElemType> *rotateLeft(TreeNode<ElemType> *);
        TreeNode<ElemType> *removeTreeNode(TreeNode<ElemType> *);
        TreeNode<ElemType> *updateHeight(TreeNode<ElemType> *);
        
        
};

/*****************************************************************************/
/*                              Implementations                              */
/*****************************************************************************/

template<typename ElemType>
AVLTree<ElemType>::AVLTree()
{
    root = nullptr;
}


template<typename ElemType>
AVLTree<ElemType>::~AVLTree()
{

}
template<typename ElemType>
bool AVLTree<ElemType>::contains(ElemType val)
{
    if (not empty())
        return contains(root, val);
    return false;

}
template<typename ElemType>
bool AVLTree<ElemType>::contains(TreeNode<ElemType> *node, ElemType val)
{
    // If TreeNode == s, return true
    if (node->value == val) {
        return true;
    } 

    // Search left subtree if TreeNode > s
    if (node->value > val and node->left != nullptr) {
        return contains(node->left, val);
    }

    // Search right subtree if TreeNode < s
    else if (node->right != nullptr) {
        return contains(node->right, val);
    } 

    // s does not exist in BST. Return false
    else {
        return false;
    }
}

template<typename ElemType>
bool AVLTree<ElemType>::empty()
{
    return (root == nullptr);
}
template<typename ElemType>
void AVLTree<ElemType>::add(ElemType val)
{
    root = add(root, val);
        
}


template<typename ElemType>
TreeNode<ElemType> *AVLTree<ElemType>::add(TreeNode<ElemType> *node, ElemType val)
{
    // Make new TreeNode 
    if (node == nullptr) {
        node = new TreeNode<ElemType>(val);

    // Insert left if currTreeNode is greater than newTreeNode
    } else if (node->value > val) {
        node->left = add(node->left, val);

    // Insert right if TreeNode is smaller than s
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
        } else { // val < TreeNode->right->value              
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    } else if (balance < -1) {
        // Left left unbalance
        if (val < node->left->value) {
            return rotateRight(node);
        // Left right unbalance
        } else { // val > TreeNode->left->value
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    return node;
}
template<typename ElemType>
ElemType AVLTree<ElemType>::pop()
{
    ElemType value = root->value;
    remove(value);
    return value;
}

template<typename ElemType>
void AVLTree<ElemType>::remove(ElemType val)
{
    root = remove(root, val);
}


template<typename ElemType>
TreeNode<ElemType> *AVLTree<ElemType>::remove(TreeNode<ElemType> *node, ElemType val)
{   
    // Standard BST removal 
    if (node == nullptr) 
        return node;
   
   // If TreeNode == val, remove TreeNode    
    if (val == node->value) 
        node = removeTreeNode(node); 

    // Search left subtree if TreeNode > s  
    else if (val < node->value)
        node->left = remove(node->left, val);
        

    // Search right subtree if TreeNode < s
    else 
        node->right = remove(node->right, val);  

    if (node == nullptr) 
        return node;
    
    // Update height
    node = updateHeight(node);

    return node;
}

template<typename ElemType>
TreeNode<ElemType> *AVLTree<ElemType>::updateHeight(TreeNode<ElemType> *node)
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
template<typename ElemType>
TreeNode<ElemType> *AVLTree<ElemType>::removeTreeNode(TreeNode<ElemType> *node)
{
    // If TreeNode has two children, find its in-order successor and replace TreeNode 
    // with it. Then delete an instance of its in-order successor through 
    // recursion
    if (node->left != nullptr and node->right != nullptr) {
        TreeNode<ElemType> *successor = getMinTreeNode(node->right);
        node->value  = successor->value;
        node->right  = remove(node->right, successor->value);
    
    // Else if TreeNode has only one or no child.
    } else {
        TreeNode<ElemType> *temp = node->left ? node->left : node->right;

        // If TreeNode has no child
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
template<typename ElemType>
TreeNode<ElemType> *AVLTree<ElemType>::getMinTreeNode(TreeNode<ElemType> *node)
{
    // Keep traversing left until end of AVL tree is reached
    if (node->left != nullptr) {
        return getMinTreeNode(node->left);
    }
    return node;
}


template<typename ElemType>
TreeNode<ElemType> *AVLTree<ElemType>::rotateLeft(TreeNode<ElemType> *node)
{
    TreeNode<ElemType> *rightChild     = node->right;
    TreeNode<ElemType> *rightLeftChild = rightChild->left;

    rightChild->left = node;
    node->right      = rightLeftChild;

    node->height       = max(height(node->left), height(node->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
    
    return rightChild;
}
template<typename ElemType>
TreeNode<ElemType> *AVLTree<ElemType>::rotateRight(TreeNode<ElemType> *node)
{
    TreeNode<ElemType> *leftChild      = node->left;
    TreeNode<ElemType> *leftRightChild = leftChild->right;

    leftChild->right = node;
    node->left       = leftRightChild;

    node->height      = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;
    return leftChild;

}

template<typename ElemType>
int AVLTree<ElemType>::getBalance(TreeNode<ElemType> *node)
{
    return (height(node->right) - height(node->left));
}

template<typename ElemType>
int AVLTree<ElemType>::height(TreeNode<ElemType> *node)
{
    if (node != nullptr)
        return node->height;
    return 0;
}

template<typename ElemType>
int AVLTree<ElemType>::max(int a, int b)
{
    return (a > b) ? a : b;
}


template<typename ElemType>
void AVLTree<ElemType>::print()
{
    std::cout << "[";
    if (not empty()) {
        print(root);
    }
    std::cout << "]";
}
template<typename ElemType>
void AVLTree<ElemType>::print(TreeNode<ElemType> *node)
{
    if (node->left != nullptr) 
        print(node->left);
    
    std::cout << node->value << " ";

    if (node->right != nullptr) 
        print(node->right);

}

template<typename ElemType>
std::stack<ElemType> AVLTree<ElemType>::getElements()
{
    std::stack<ElemType> elemStack;
    getElements(root, elemStack);
    return elemStack;    
}

template<typename ElemType>
void AVLTree<ElemType>::getElements(TreeNode<ElemType> *node, std::stack<ElemType> &elemStack)
{
    if (node != nullptr) {
        elemStack.push(node->value);
        getElements(node->left, elemStack);
        getElements(node->right, elemStack);
    }
    
}
template<typename ElemType>
void AVLTree<ElemType>::printTree()
{
    std::cout << "[";
    if (not empty()) {
        printTree(root);
    }
    std::cout << "]" << std::endl;
}
template<typename ElemType>
void AVLTree<ElemType>::printTree(TreeNode<ElemType> *node)
{
    // Traverse left subtree 
    std::cout << "[";
    if (node->left != nullptr) {    
        printTree(node->left);  
    } 
    // Print current TreeNode
    std::cout << "] " << node->value << " [";
    
    // Traverse right subtree
    if (node->right != nullptr) {
        printTree(node->right);
    }
    std::cout << "]";
    
}
template<typename ElemType>
int AVLTree<ElemType>::size()
{
    return size(root, 0);
}
template<typename ElemType>
int AVLTree<ElemType>::size(TreeNode<ElemType> *node, int sum)
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
template<typename ElemType>
ElemType AVLTree<ElemType>::getRoot()
{
    return root->value;
}
#endif