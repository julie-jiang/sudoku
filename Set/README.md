# Set
This is implemented as an [AVL tree](https://en.wikipedia.org/wiki/avl_tree), a type of self-balancing binary search tree. As a set, it will not hold duplicate copies of the same item. If you attempt to add an element that is already in the set, then nothing will change.


## Initialization 
To initialize a `Set` object:

```c++
#include "Set.h"
// ...
Set<T> set;
Set<T> *set_pointer = new Set<T>;

Set<T> copy_set(set);
Set<T> *copy_set_pointer = new Set<T>(set);
```


## The things it can do

1. Add an element

    ```c++
    set.add(item)
    ```

2. Remove an element (without returning)

    ```c++
    set.remove(item);
    ```
3. Get the root of the set (without removing)

    ```c++
    T item = set.top();
    ```
4. Get and remove the root of the set
    
    ```c++
    T item = set.pop();
    ```

5. Check if it contains an element in O(n) time (returns a bool)

    ```c++
    if (set.contains(item)) {
        // ...
    }
    ```
    
6. Check if its empty (returns a bool)

    ```c++
    if (set.empty()) {
        // ...
    }
    ```

7. Get the size of the set

    ```c++
    size_t size = set.size()
    ```

8. Iterate through the set
    
    ```c++
    for (Set<T>::iterator it = set.begin(); it != set.end(); ++it) {
        std::cout << *it << std::endl;
    }
    ```
    
7. Print the elements in the set via in order traversal

    ```c++
    set.print()
    ```

8. Print the set tree with a bunch of brackets indicating parent-child relationship. This is mostly for debugging at the moment and will probably be removed later.

    ```c++
    set.printTree()
    ```

## Testing
Compile with:

```
make
```

And run:

```
./testSet
```

