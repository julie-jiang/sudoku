# AVLTree.h
An [AVL tree](https://en.wikipedia.org/wiki/AVL_tree) is a self-balancing binary search tree. This tree is designed to hold the domain, or possible values, each variable in the grid can hold. In practice, it can hold elements of any type.

## Initialization 
To initialize an `AVLTree` object:

    ```c++
    #include "AVLTree.h"
    // ...
    AVLTree<ElemType> avl;
    ```

## The things it can do

1. Add an element

    ```c++
    avl.add(item)
    ```

2. Remove an element (without returning)

    ```c++
    avl.remove(item);
    ```

3. Check if it contains an element in O(n) time (returns a bool)

    ```c++
    if (avl.contains(item)) {
        // ...
    }
    ```
    
3. Check if its empty (returns a bool)

    ```c++
    if (avl.empty()) {
     // ...
    }
    ```

4. Get the size of the tree

    ```c++
    int size = avl.size()
    ```

5. Get the root of the tree (without removing)

    ```c++
    ElemType item = avl.getRoot()
    ```

7. Get all the elements in the tree as a stack (This is mostly for convenience at the moment, might be eliminated in the final version)

    ```c++
    #include <cstdlib>
    #include <stack>
    // ...
    stack<ElemType> elements = avl.getElements()
    ```

6. Print the elements in the tree via in order traversal

    ```c++
    avl.print()
    ```

7. Print the tree with a bunch of brackets indicating parent-child relationship. This is mostly for debugging at the moment and will probably be removed later.

    ```c++
    avl.printTree()
    ```

## Testing
Compile with:

    ```
    make
    ```
And run:

    ```
    ./testAVLTree
    ```

