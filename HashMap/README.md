# Hash Map
This hash map is designed to hold Key-Value pairs, in which the keys would be `Coord` objects and the values would be the integer that is assigned to the `Coord`. In practice, it can hold keys and values of any type. 

Hash collisions will be resolved by chaining. This hash table will not be able to resize or rehash, so if the number of values get too out of hand there will be a lot of hash collisions. It is therefore important to have a relative maximum bound in mind when initializing this object.

This data structure is currently still under development.

## Intialization
To create a new hashtable of default bucket size of 100:

```c++
#include "Hashtable.h"
// ...
HashTable<std::string, int> ht;
```

To create a new hashtable of with user defined bucket size:

```c++
#include "Hashtable.h"
// ...
int size = 200;
HashTable<std::string, int> ht(size);
```
## The things it can do

1. Look up the value of a given key. It will return some sort of none if the key is not present. 

2. Insertion and removal 

## Testing
Compile with:
```
make
```
And run:
```
./testHashTable
```
