# Hash Table
This is an unordered collection of elememts (or values) indexed by keys. Values 
can be anything, and keys can be any immutable types that can be converted to 
strings. 

Because values are indexed by keys, keys must be immutable, meaning they cannot 
be changed. Values, however, can be changed or overwritten. Which means that 
keys should be unique to ensure that no data is lost. Due to the way that the 
keys are hashed, the keys must also be able to be converted to a string.

Hash collision is resolved by chaining. Therefore, the hash table is 
implemented as a bunch of `buckets`, each `bucket` is a `LinkedList` object (see 
[LinkedList](../LinkedList)), which in turn holds a bunch of `ListNodes`. In 
order to reduce hash collisions, the size of the `bucket` is always a prime 
number. 

When the load factor (defined to be the number of elements stored in the hash 
table divided by the number of buckets) is larger than the threshold 0.75, then 
the buckets will be resized to the smallest prime number greater than 
`bucketSize * 2`. 

The keys are hashed by their string form using the hash function included
in `<functional>`. 

## Intialization
To create a new Hash Table of default bucket size of 101:

```c++
HashTable<std::string, int> ht;
```

To create a new Hash Table with at least 200 buckets:

```c++
size_t size = 200;
HashTable<std::string, int> sized_ht(size);
```

Copy constructor and assignment overload:
```c++
HashTable<std::string, int> ht_copy(ht);
HashTable<std::string, int> ht_assigned = ht;
```

## The things it can do

1. Inserts key value pair to the hash table. If the key already exists, then 
   its value will be overwritten with the new value. 
    ```c++
    ht.insert("key1", 10);
    ht.insert("key1", 20); // value of "key1" is now 20
    ```

2. Get value using subscript operator. Will throw logic error if key does not 
   exist.
    
    ```c++
    int val = ht["key1"];                         // val = 20
    int nonexistent_val = ht["nonexistent_key"];  // this will throw error
    ```

3. Remove a value using a key without returning anything. If the key does not 
   exist in the map, then nothing will be changed.

    ```c++
    ht.remove("key1");            // "key1" is now reomved 
    ht.remove("nonexistent_key"); // Nothing happens
    ```

4. Resize the hash table. The new hash table size is a prime number that is at 
   least as large the given parameter.

    ```c++
    ht.resize(500); // The size of the hash table now is actually 503, the smallest prime number >= 500 
    ```

5. Iterate through the keys of the map. The order is not in order of insertion.

    ```c++
    for (HashTable<std::string, int>::key_iterator it = ht.begin(); 
         it != ht.end(); ++it) {
        std::string key   = it.key();
        int         value = it.value();
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
./testHashTable
```
