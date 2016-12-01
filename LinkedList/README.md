# Linked List
This is the linked list used in the [Hash Table][1]. The nodes in 
the linked list consist of a key and a value.

## Intialization
To create a new linked list with strings as keys and ints as values

```c++
LinkedList<std::string, int> list;
```
## The things it can do

1. Insert a new value. Returns false if key already exists, in which case the 
   old value will be overwritten with the new one.
    
    ```c++
    list.insert("key1", 10); // Returns true
    list.insert("key1", 20); // Returns false and value of "key1" is now 20
    ```

2. Get value using subscript operator. Will throw logic error if key does not 
   exist
    
    ```c++
    int val = list["key1"]; // val = 20
    ```

3. Remove a value using a key. Returns true if key is found and node is 
   removed.

    ```c++
    list.remove("key1"); // Returns true
    list.remove("key2"); // Returns false
    ```

4. Get the size of the linkedlist.
    
    ```c++
    size_t size = list.size();
    ```

5. Check if list is empty

    ```c++
    if (list.empty()) {
        // ... do something
    }
    ```

6. Iterate through the list.

    ```c++
    for (LinkedList<std::string, int>::iterator it = list.begin(); 
         it != list.end(); ++it) {
        std::string key   = list.key();
        int         value = list.value();
        // ... do something
    }
    ```
    
## Testing
Compile with:

```
make
```

And run:
```
./testLinkedList
```
[1]: ../HashTable