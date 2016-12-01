/* 
   Coord.h
   Header file for the object Coord. It is similar to std::pair, as it holds
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
   The first integer stored in a Coord is defined to be its x-coordinate, or 
   `x`, and the second integer stored is defined to be its y-coordinate, or 
   `y`. A Coord `c1` is greater than another Coord `c2` if either 
   `c1.x > c2.x` or `c1.x == c2.x` and `c1.y > c2.y`. 
   Same logic applies to other equality operators.

   A Coord object is immutable, meaning its values cannot be changed once it's
   created.
 */
#ifndef COORD_H
#define COORD_H
#include <iostream>

class Coord {

    public:
        Coord(int, int);       // Constructor 
        Coord(const Coord &);  // Copy constructor 

        // Equality operators
        friend bool operator==(const Coord &, const Coord &);
        friend bool operator!=(const Coord &, const Coord &);
        friend bool operator<=(const Coord &, const Coord &);
        friend bool operator<(const Coord &, const Coord &);
        friend bool operator>=(const Coord &, const Coord &);
        friend bool operator>(const Coord &, const Coord &);

        // Ostream operator
        friend std::ostream &operator<<(std::ostream &, const Coord &);

        // Subscript operator
        int &operator[](const int);

    private:
        int x;
        int y;
};

#endif