/* 
   Coord.cpp
   Implementaions for the object Coord. It is similar to std::pair, as it holds
   a pair of integers, but it is optimized specifically to hold the coordinates
   of a set of coordinates for the Soduku program. 
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* To initialize a instance of the object Coord that holds values 1 and 2:
        Coord c(1, 2);
   To access the individual elements of a Coord:
        int x = c[0];
        int y = c[1];
   To print a Coord via standard cout:
        std::cout << c; // print as "(1, 2)" 
   To compare the two Coords:
        if (c1 > c2) {
            // ... do something
        } 
   A Coord object is immutable, meaning its values can't be changed once it's
   been constructed.
 */
#include <iostream>
#include "Coord.h"

/* Constructor */
Coord::Coord(int i, int j) {
    x = i;
    y = j;
}
/* Copy constructor */
Coord::Coord(const Coord &source) {
    x = source.x;
    y = source.y;
}
/* Equality operator "==". */
bool operator==(const Coord &source1, const Coord &source2) {
    return (source1.x == source2.x and source1.y == source2.y);
}
/* Equality operator "!=" */
bool operator!=(const Coord &source1, const Coord &source2) {
    return not (source1 == source2);
}
/* Equality operator "<=" */
bool operator<=(const Coord &source1, const Coord &source2) {
    return (source1 < source2 or source1 == source2);

}
/* Equality operator "<" */
bool operator<(const Coord &source1, const Coord &source2) {
    return (source1.x < source2.x or 
           (source1.x == source2.x and source1.y < source2.y));
}
/* Equality operator ">=" */
bool operator>=(const Coord &source1, const Coord &source2) {
    return (source1 > source2 or source1 == source2);
}
/* Equality operator ">" */
bool operator>(const Coord &source1, const Coord &source2) {
    return not (source1 <= source2);
}
/* Subscript operator 
   Index must be either 0 or 1. Else logic error would be thrown. */
int &Coord::operator[](const int index) {
    if (index == 0) {
        return x;
    } else if (index == 1) {
        return y;
    }
    throw std::logic_error("Coord: index error");
}
/* Ostream operator "<<". If x = 1 and y = 2, then output would be "(1, 2)" */
std::ostream &operator<<(std::ostream &output, const Coord &source) {
    output << "(" << source.x << ", " << source.y << ")";
    return output;
}