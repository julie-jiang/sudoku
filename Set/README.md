# Set
This is an ordered collection of unique elements, implemented as an [AVL tree]
(https://en.wikipedia.org/wiki/avl_tree), a type of self-balancing binary 
search tree. 

As a set, it will not hold duplicate copies of the same item. If you attempt to
add an element that is already in the set, then nothing will change. 

As an AVL Tree, in addtion to the value and pointers to children nodes, each 
node in the set also has a balance. At each insertion or removal, balance is 
maintained by rotating some of the unbalanced subtrees.

The benefits of using this container is the fast O(n) look up time, which comes
at the cost of slower insertion and removal.


## Initialization 
To initialize a `Set` object:

```c++
Set<T> set;            // Constructor 
Set<T> copy_set(set);  // Copy constructor
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
        // ... do something
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
    
7. Use standard output to print all the elements in the set via in order 
   traversal

    ```c++
    Set<int> numbers;
    for (int i = 1; i <= 5; i++) {
        numbers.add(i);
    }
    std::cout << set; // [1, 2, 3, 4, 5]
    ```

8. Get the tree form of the set as a string. 
   For example, consider a set with the elements 10, 20, 30, 40, 50, and 60:
    ```c++
    Set<int> numbers;
    for (int i = 1; i <= 60; i += 10) {
        numbers.add(i);
    }
    std::cout << numbers.tree();
    ```

   This will produce the following 
    ```
    30                  
        50               
            60          
            40    
        20         
            10                      
    ```
    Which represents the tree 
    ```
         30
        /  \
       20  50
      /   /  \
     10  40  60
    ```
    This is particularly useful for debugging.

## Testing
Compile with:

```
make
```

And run:

```
./testSet
```

