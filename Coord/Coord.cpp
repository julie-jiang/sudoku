#include <iostream>
#include "Coord.h"

Coord::Coord(int i, int j) 
{
    x = i;
    y = j;
}
Coord::Coord(const Coord &source)
{
    x = source.x;
    y = source.y;

}
bool operator==(const Coord &source1, const Coord &source2) 
{
    return (source1.x == source2.x and source1.y == source2.y);
}
bool operator!=(const Coord &source1, const Coord &source2) 
{
    return not (source1 == source2);
}
int &Coord::operator[](const int index)
{
    if (index == 0) {
        return x;
    } else if (index == 1) {
        return y;
    }
    throw std::logic_error("Coord: index error");
}
std::ostream &operator<<(std::ostream &output, const Coord &source)
{
    output << "(" << source.x << ", " << source.y << ")";
    return output;
}