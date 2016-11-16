/*
 * Easy to add element 
 * Easy to remove element
 * Easy to find element
 */

/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/

#ifndef AVLTree_H
#define AVLTree_H
#include <cstdlib>
#include <stack>

template<typename ElemType>


class AVLTree {
    public:
        AVLTree();
        ~AVLTree();
        void add(ElemType);
        bool contains(ElemType);
        void remove(ElemType);
        bool empty();
        int size();
        void print();
        void printTree();
        ElemType getRoot();
        std::stack<ElemType> getElements();
    private:
        struct Node {
            int height;
            ElemType value;
            Node *left;
            Node *right;
        }
        *root;

        Node *add(Node *, ElemType);
        Node *makeNewNode(ElemType);
        bool contains(Node *, ElemType);
        Node *remove(Node *, ElemType);
        void print(Node *);
        void printTree(Node *);
        void getElements(Node *, std::stack<ElemType> &);
        int size(Node *, int);
        
        int getBalance(Node *);
        int height(Node *);
        int max(int, int);
        Node *getMinNode(Node *);
        Node *rotateRight(Node *);
        Node *rotateLeft(Node *);
        Node *removeNode(Node *);
        Node *updateHeight(Node *);
        
        
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
bool AVLTree<ElemType>::contains(Node *node, ElemType val)
{
    // If node == s, return true
    if (node->value == val) {
        return true;
    } 

    // Search left subtree if node > s
    if (node->value > val and node->left != nullptr) {
        return contains(node->left, val);
    }

    // Search right subtree if node < s
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
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::add(Node *node, ElemType val)
{
    // Make new node 
    if (node == nullptr) {
        node = makeNewNode(val);

    // Insert left if currnode is greater than newnode
    } else if (node->value > val) {
        node->left = add(node->left, val);

    // Insert right if node is smaller than s
    } else {
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
        } else { // val < node->right->value              
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    } else if (balance < -1) {
        // Left left unbalance
        if (val < node->left->value) {
            return rotateRight(node);
        // Left right unbalance
        } else { // val > node->left->value
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    return node;
}

template<typename ElemType>
void AVLTree<ElemType>::remove(ElemType val)
{
    root = remove(root, val);
}


template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::remove(Node* node, ElemType val)
{   
    // Standard BST removal 
    if (node == nullptr) 
        return node;
   
   // If node == val, remove node    
    if (val == node->value) 
        node = removeNode(node); 

    // Search left subtree if node > s  
    else if (val < node->value)
        node->left = remove(node->left, val);
        

    // Search right subtree if node < s
    else 
        node->right = remove(node->right, val);  

    if (node == nullptr) 
        return node;
    
    // Update height
    node = updateHeight(node);

    return node;
}

template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::updateHeight(Node *node)
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
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::removeNode(Node *node)
{
    // If node has two children, find its in-order successor and replace node 
    // with it. Then delete an instance of its in-order successor through 
    // recursion
    if (node->left != nullptr and node->right != nullptr) {
        Node *successor = getMinNode(node->right);
        node->value  = successor->value;
        node->right  = remove(node->right, successor->value);
    
    // Else if node has only one or no child.
    } else {
        Node *temp = node->left ? node->left : node->right;

        // If node has no child
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
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::getMinNode(Node *node)
{
    // Keep traversing left until end of AVL tree is reached
    if (node->left != nullptr) {
        return getMinNode(node->left);
    }
    return node;
}


template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::rotateLeft(Node *node)
{
    Node *rightChild     = node->right;
    Node *rightLeftChild = rightChild->left;

    rightChild->left = node;
    node->right      = rightLeftChild;

    node->height       = max(height(node->left), height(node->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
    
    return rightChild;
}
template<typename ElemType>
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::rotateRight(Node *node)
{
    Node *leftChild     = node->left;
    Node *leftRightChild = leftChild->right;

    leftChild->right = node;
    node->left       = leftRightChild;

    node->height      = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;
    return leftChild;

}

template<typename ElemType>
int AVLTree<ElemType>::getBalance(Node *node)
{
    return (height(node->right) - height(node->left));
}

template<typename ElemType>
int AVLTree<ElemType>::height(Node *node)
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
typename AVLTree<ElemType>::Node *AVLTree<ElemType>::makeNewNode(ElemType val)
{
    Node *newNode   = new Node;
    newNode->height = 1;
    newNode->value  = val;
    newNode->left   = nullptr;
    newNode->right  = nullptr;
    return newNode;
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
void AVLTree<ElemType>::print(Node *node)
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
void AVLTree<ElemType>::getElements(Node *node, std::stack<ElemType> &elemStack)
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
void AVLTree<ElemType>::printTree(Node *node)
{
    // Traverse left subtree 
    std::cout << "[";
    if (node->left != nullptr) {    
        printTree(node->left);  
    } 
    // Print current node
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
int AVLTree<ElemType>::size(Node *node, int sum)
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