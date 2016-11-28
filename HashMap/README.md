# Hash Map
This hash map is designed to hold Key-Value pairs, in which the keys would be `Coord` objects and the values would be the integer that is assigned to the `Coord`. In practice, it can hold keys and values of any type. 

A key is hashed by turning that key into its string form and hashing the string. This hash map would not be able to work with keys that cannot be turned into strings.

Hash collisions will be resolved by chaining. Each bucket in the hash map holds a [linked list](LinkedList/). This hash table will not be able to resize or rehash, so if the number of values get too out of hand there will be a lot of hash collisions. It is therefore important to have a relative maximum bound in mind when initializing this object.

This map is also a linked hash map. The additional memory space used to keep an additional linked list to hold all the nodes stored in the map is compensated  by faster iteration.

## Intialization
To create a new hash map of default bucket size of 100:

```c++
#include "HashMap.h"
// ...
HashMap<std::string, int> map;
```

To create a new hash map with user defined bucket size:

```c++
#include "HashMap.h"
// ...
size_t size = 200;
HashMap<std::string, int> map(size);
```
## The things it can do

1. Insert a new value. If you attempt to insert a pair of value whose key already exists in the linkedlist, then the value for that key will be overwritten with the new value.
    ```c++
    map.insert("key1", 10);
    map.insert("key1", 20); // value of "key1" is now 20
    ```

2. Get value using subscript operator. Will throw logic error if key does not exist
    
    ```c++
    int val = map["key1"]; // val = 20
    ```

3. Remove a value using a key without returning anything. If the key does not exist in the map, then nothing will be changed.

    ```c++
    map.remove("key1");
    ```

4. Iterate through the keys of the map. The order is not in order of insertion.

    ```c++
    for (HashMap<std::string, int>::key_iterator it = map.begin(); it != map.end(); ++it) {
        std::string key = *it;
        int value = map[*it];
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
./testHashMap
```
