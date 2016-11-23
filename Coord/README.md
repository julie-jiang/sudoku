# Coord
The variables in `Soduku`, which are the individual grid cells, are implemented as instances of the `Coord` object, short for coordinates. It simply holds two integers x and y that specify where in the grid this object refers to.

## Initilization

```c++
#include "Coord.h"
// ...
Coord c(1, 2);
```

## The things it can do

1. Equality operators 
    ```c++
    Coord c1(1, 1);
    Coord c2(1, 1);
    Coord c3(1, 2);
    assert(c1 == c2); 
    assert(c1 != c3);
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
