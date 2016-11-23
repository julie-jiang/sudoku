#ifndef COORD_H
#define COORD_H
#include <iostream>

class Coord {

    public:
        Coord(int, int);
        Coord(const Coord &);
        friend bool operator==(const Coord &, const Coord &);
        friend bool operator!=(const Coord &, const Coord &);
        friend bool operator<=(const Coord &, const Coord &);
        friend bool operator<(const Coord &, const Coord &);
        friend bool operator>=(const Coord &, const Coord &);
        friend bool operator>(const Coord &, const Coord &);

        friend std::ostream &operator<<(std::ostream &, const Coord &);
        int &operator[](const int);

    private:
        int x;
        int y;
};

#endif