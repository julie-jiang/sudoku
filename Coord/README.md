# Coord
Coord is similar to std::pair, as it holds a pair of integers, but it is 
optimized specifically to hold the coordinates of a set of coordinates for the
Soduku program. 

The first integer stored in a Coord is defined to be its x-coordinate, or `x`, 
and the second integer stored is defined to be its y-coordinate, or `y`. A Coord
`c1` is greater than another Coord `c2` if either `c1.x > c2.x` or `c1.x == c2.x`
and `c1.y > c2.y`. Same logic applies to other equality operators.

A Coord object is immutable, meaning its values cannot be changed once it's 
created.
## Initilization

```c++
#include "Coord.h"
// ...
Coord c1(1, 2);  // constructor
Coord c2(c);     // copy constructor
```

## The things it can do

1. Equality operators 
    ```c++
    Coord c1(1, 1);
    Coord c2(1, 1);
    Coord c3(1, 2);
    assert(c1 == c2); 
    assert(c1 != c3);
    assert(c1 <  c3);
    assert(c1 <= c2);
    ```

2. Subscript operator
    ```c++
    Coord c(1, 2);
    int x = c[0];
    int y = c[1];
    std::cout << "x = " << x << std::endl; // x = 1
    std::cout << "y = " << y << std::endl; // x = 2
    ```
3. Cout as string

    ```c++
    Coord c(1, 2);
    std::cout << c << std::endl; // (1, 2)
    ```

## Testing
Compile with:

```
make
```

And run:

```
./testCoord
```
