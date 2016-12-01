/* 
   Set.h
   Header and implementations of the container Set, an ordered collection of
   unique elements. It is implemented as an AVL Tree, a self-balancing binary
   search tree. 
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project                                     */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* Create an instance of Set with either the constructor or the copy 
   constructor. Once created, you can
      (1) add an element
      (2) remove an element without returning
      (3) get the value at the root of the Set without removing
      (4) get and remove the value at the root of the Set
      (5) check if the Set contains a certain element
      (6) check if the Set is empty
      (7) get the number of elements stored in the Set
      (8) iterate through the Set
      (9) print the elements of the set using ostream operator "<<"
      (10) get the tree form of the set as a string

   For more usage information and examples, please see the README.md in this 
   directory.                                                                */
/*****************************************************************************/
/*                         Implementation details                            */
/*****************************************************************************/
/* In addtion to the value and pointers to children nodes, each node 
   (see SetNode) also has a balance. At each insertion or removal, balance is
   maintained by rotating some of the unbalanced subtrees.                   */
/*****************************************************************************/
/*                                  Header                                   */
/*****************************************************************************/
#ifndef SET_H
#define SET_H
#include <iostream>
#include <sstream>
#include "SetNode.h"
#include "SetIterator.h"
template<typename T>
class Set;
template<typename T>
std::ostream &operator <<(std::ostream &, const Set<T> &);

template<typename T>
class Set {
    public:
        Set();                  
        ~Set();
        Set(const Set &); // Copy constructor
        void        add(T);       
        void        remove(T);    
        bool        contains(T); 
        T           top(); // Get the root of the set without removing
        T           pop(); // Get the root of the set and remove it
        bool        empty();
        size_t      size();
        std::string tree(); // Get the string form of the tree of the set

        typedef SetIterator<T> iterator; // Iterator functions 
        iterator    begin() const;
        iterator    end()   const;
        // Overload ostream operator
        friend std::ostream &operator << <>(std::ostream &, const Set &);
    private:
        SetNode<T> *root;
        SetNode<T> *add(SetNode<T> *, T);
        SetNode<T> *remove(SetNode<T> *, T);
        SetNode<T> *removeSetNode(SetNode<T> *);
        SetNode<T> *getMinSetNode(SetNode<T> *);

        int         getBalance(SetNode<T> *);
        SetNode<T> *restoreBalance(SetNode<T> *);
        SetNode<T> *rotateRight(SetNode<T> *);
        SetNode<T> *rotateLeft(SetNode<T> *);
        int         max(int, int);
        
        bool        contains(SetNode<T> *, T);
        size_t      size(SetNode<T> *, int);
        int         height(SetNode<T> *);
        void        clear(SetNode<T> *);

        void        tree(SetNode<T> *, int, std::string &);
        void        toString(SetNode<T> *, std::string &) const;
        std::string value2string(T &) const;      
};

/*****************************************************************************/
/*                          Big Three Implementations                        */
/*****************************************************************************/
/* Constructor */
template<typename T>
Set<T>::Set() {
    root = nullptr;
}

/* Destructor */
template<typename T>
Set<T>::~Set() {
    if (not empty()) {
        clear(root);
    }
}
/* Destructor helper function. Recursively delete every node in the set via 
   post-order traversal */
template<typename T>
void Set<T>::clear(SetNode<T> *node) {
    if (node->left != nullptr) {
        clear(node->left);
    }
    if (node->right != nullptr) {
        clear(node->right);
    }
    delete node;
}
/* Copy constructor */
template<typename T>
Set<T>::Set(const Set &source) {
    root = nullptr;
    for (Set<T>::iterator i = source.begin(); i != source.end(); ++i) {
        add(*i);
    }

}
/*****************************************************************************/
/*                                    Add                                    */
/*****************************************************************************/

/* Adds val to the tree. No changes if the val already exists */
template<typename T>
void Set<T>::add(T val) {
    root = add(root, val);
        
}

/* add helper function. Adds val to the tree recursively via pre-order 
   traversal. First perform a standard BST insertion. Then restores balance if 
   need be. Returns the updated version of the input node. */
template<typename T>
SetNode<T> *Set<T>::add(SetNode<T> *node, T val) {
    if (node == nullptr) {// Make new SetNode
        node = new SetNode<T>(val);

    } else if (node->value > val) {  // Insert left
        node->left = add(node->left, val);

    } else if (node->value < val) { // Insert right
        node->right = add(node->right, val);
    }
    return restoreBalance(node);
}
/*****************************************************************************/
/*                                   Remove                                  */
/*****************************************************************************/
/* Removes the value from the tree if it exists. If it doesn't exist, nothing
   will change. */
template<typename T>
void Set<T>::remove(T val) {
    root = remove(root, val);
}

/* remove helper function. Recursively searches for the val via pre-order 
   traversal. First perform a standard BST removal. Then restores balance
   if need be. */
template<typename T>
SetNode<T> *Set<T>::remove(SetNode<T> *node, T val) {   
    // Standard BST removal 
    if (node == nullptr) {
        return node;
    }
    if (val == node->value)  { // If SetNode == val, remove SetNode  
        node = removeSetNode(node); 
    }
    else if (val < node->value) {  // Search left subtree if SetNode > s  
        node->left = remove(node->left, val);
    }
    else if (val > node->value) {  // Search right subtree if SetNode < s
        node->right = remove(node->right, val);  
    }
    if (node == nullptr) { // Don't need to update height if node is nullptr
        return node;
    }
    return restoreBalance(node); // maintain balance

}
/* Removes the node from the tree. This is the same as a standard BST removal,
   for which there are three possible cases to consider. The node to be removed
   may have two children, one child, or no child. Returns the memory address
   of the original node. */
template<typename T>
SetNode<T> *Set<T>::removeSetNode(SetNode<T> *node) {
    // If node has two children, replace the contents of this node with 
    // those of its in-order successor.
    // Then delete its original in-order successor through recursion.
    if (node->left != nullptr and node->right != nullptr) {
        SetNode<T> *successor = getMinSetNode(node->right);
        node->value  = successor->value;
        node->right  = remove(node->right, successor->value);
    
    
    } else { // else if node has only one or no child.
        SetNode<T> *temp = node->left ? node->left : node->right;
        if (temp == nullptr) {  // If node has no child
            temp = node;
            node = nullptr;
        } else {                // else node has no children
            *node = *temp;
        }
        delete temp;            // Whichever the case, delete the node
    }
    return node;
}
/* Find the minimum node starting from the given node. */
template<typename T>
SetNode<T> *Set<T>::getMinSetNode(SetNode<T> *node) {
    // Keep traversing left until end of AVL tree is reached
    return (node->left == nullptr) ? node : getMinSetNode(node->left);
}
/*****************************************************************************/
/*                        Balance restoring function                         */
/*****************************************************************************/
/* Updates the height of this node and fixes any unbalance. Balance is defined
   to be the height of the node's right subtree - the height of the node's
   left subtree. If balance > 1, then the right subtree is unbalanced. If
   balance < -1, then the left subtree is unbalanced.

   There are four possible cases to consider: right right unbalance, 
   right left unbalance, left left unbalance, and left right unbalance.
   Returns the memory address of the balanced node. */
template<typename T>
SetNode<T> *Set<T>::restoreBalance(SetNode<T> *node) {
    // Update height and get balance
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);
        
    if (balance > 1) {
        if (getBalance(node->right) >= 0) { // Right right unbalance   
            return rotateLeft(node);

        } else {                            // Right left unbalance 
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    } else if (balance < -1) {
        if (getBalance(node->left) <= 0) { // Left left unbalance
            return rotateRight(node);
        
        } else {                          // Left right unbalance
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    return node;
}

/* Rotates the subtree with this node at root left. Returns the new root
   of this rotated subtree. */ 
template<typename T>
SetNode<T> *Set<T>::rotateLeft(SetNode<T> *node) {
    SetNode<T> *rightChild     = node->right;
    SetNode<T> *rightLeftChild = rightChild->left;
    // Rotation 
    rightChild->left = node;           
    node->right      = rightLeftChild;
    // Update heights
    node->height       = max(height(node->left), height(node->right)) + 1;
    rightChild->height = max(height(rightChild->left), 
                             height(rightChild->right)) + 1;
    return rightChild;
}
/* Rotates the subtree with this node at root right. Returns the new root
   of this rotated subtree. */ 
template<typename T>
SetNode<T> *Set<T>::rotateRight(SetNode<T> *node) {
    SetNode<T> *leftChild      = node->left;
    SetNode<T> *leftRightChild = leftChild->right;
    // Rotation
    leftChild->right = node;
    node->left       = leftRightChild;
    // Update heights
    node->height      = max(height(node->left), height(node->right)) + 1;
    leftChild->height = max(height(leftChild->left), 
                            height(leftChild->right)) + 1;
    return leftChild;
}
/* Returns the balance at this node */
template<typename T>
int Set<T>::getBalance(SetNode<T> *node) {
    return (height(node->right) - height(node->left));
}
/* Returns the height of this node. If the node does not exist (i.e. node is 
   nullptr), then the height is 0 */
template<typename T>
int Set<T>::height(SetNode<T> *node) {
    return (node == nullptr) ? 0 : node->height;
}

/* Return the maximum of the two integer */
template<typename T>
int Set<T>::max(int a, int b) {
    return (a > b) ? a : b;
}
/*****************************************************************************/
/*                                  Contains                                 */
/*****************************************************************************/

/* Returns true if the set contains val. */
template<typename T>
bool Set<T>::contains(T val) {
    return (empty()) ? false : contains(root, val);
}
/* contains helper function. Recursively check if the set contains val.
   Returns true if this node or any of its children contains val. */
template<typename T>
bool Set<T>::contains(SetNode<T> *node, T val) {
    // Found s! 
    if (node->value == val) { 
        return true;
    } 
    // Search left subtree if SetNode > s
    if (node->value > val and node->left != nullptr) {   
        return contains(node->left, val);               
    }
    // Search right subtree if SetNode <= s
    else if (node->right != nullptr) {          
        return contains(node->right, val);             
    } 
    // Else, s does not exist in BST
    return false;
}
/*****************************************************************************/
/*                                   Empty                                   */
/*****************************************************************************/
/* Returns true if set is empty. */
template<typename T>
bool Set<T>::empty() {
    return (root == nullptr);
}

/*****************************************************************************/
/*                               Get Root                                    */
/*****************************************************************************/
/* Returns the value of the root of the tree. */
template<typename T>
T Set<T>::top() {
    return root->value;
}

/* Returns the value of the root of the tree AND removes it from the tree */
template<typename T>
T Set<T>::pop() {
    T value = root->value;
    remove(value);
    return value;
}


/*****************************************************************************/
/*                                  Size                                     */
/*****************************************************************************/
/* Returns the number of elements stored in the tree */
template<typename T>
size_t Set<T>::size() {
    return size(root, 0);
}
/* size helper function. Recursively sum up the number of elements in the tree
   via pre-order traversal. Returns the number of elements in the tree. */
template<typename T>
size_t Set<T>::size(SetNode<T> *node, int sum) {
    if (node != nullptr) {
        sum++;
        sum = size(node->left, sum);   // Traverse left subtree 
        sum = size(node->right, sum);  // Traverse right subtree
    }
    return sum;
}
/*****************************************************************************/
/*                             Output Functions                              */
/*****************************************************************************/

/* Overload the ostream operator "<<". Outputs all the elements in the list
   in order. For example, if the set contains the integers 4, 6, 2, 3, and 7, 
   then this will return "[2, 3, 5, 6, 7]". If the set is empty, then 
   it will return "[]". */ 
template<typename T>
std::ostream &operator<<(std::ostream &output, const Set<T> &source) {
    std::string str = "[";
    if (source.root != nullptr) {
        source.toString(source.root, str);
        str.erase(str.size() - 2);  // Remove the last comma
    }
    str += "]";
    output << str;
    return output;
}
/* Ostream operator "<<" overload helper function. Recursively build
   a string version of all the elements in the tree via in-order traversal.*/
template<typename T>
void Set<T>::toString(SetNode<T> *node, std::string &str) const {
    if (node->left != nullptr) 
        toString(node->left, str);
    
    str += (value2string(node->value) + ", ");

    if (node->right != nullptr) 
        toString(node->right, str);
}

/* Returns a tree version of the set as a string. For example, if 
   set contains the integers 30, 50, 60, 40, 20 and 10, then tree() will 
   return:
    30                                                 30
        50                                            /   \
            60          which is the same as         /     \
            40                                      20     50
        20                                         /      /  \  
            10                                    10     40  60
   Which means that the root of the tree is 30. 30's right child is 50, and 
   30's left child is 20. 50 has two children, which are 60 and 40. 20 has
   one child, which is 10. Every new level of the tree is indented by 4 
   additional spaces. 
   This is particularly useful for debugging.
*/
template<typename T>
std::string Set<T>::tree() {
    std::string str_tree = "";
    if (not empty()) {
        tree(root, 0, str_tree);
    }
    return str_tree;
}
/* tree helper function. Recursively build the string version of the tree
   via pre-order traversal */
template<typename T>
void Set<T>::tree(SetNode<T> *node, int depth, std::string &str_tree) {
    std::string indent = "";
    for (int i = 0; i < depth; i++) {
        indent += "    "; 
    }
    str_tree += (indent + value2string(node->value) + "\n");
    if (node->right != nullptr) {
        tree(node->right, depth + 1, str_tree);
    }
    if (node->left!= nullptr) {
        tree(node->left, depth + 1, str_tree);
    }

}
/* Output helper function. Converts the given value of type T to a string */
template<typename T>
std::string Set<T>::value2string(T &v) const {
    std::string result;
    std::ostringstream oss;
    oss << v;
    return oss.str();
}

/*****************************************************************************/
/*                           Iterator Functions                              */
/*****************************************************************************/

/* Return a SetIterator object of the root */
template<typename T>
SetIterator<T> Set<T>::begin() const {
    return SetIterator<T>(root);
}

/* Return a SetIterator object of nullptr */
template<typename T>
SetIterator<T> Set<T>::end() const {
    return SetIterator<T>(nullptr);
}


#endif