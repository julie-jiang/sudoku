#include <iostream>
#include "HashMap.h"
#include "../Coord/Coord.h"

int main ()
{
    HashMap<std::string, int> ht1;
    ht1.set("a", 1);
    ht1.set("b", 2);
    int aval = ht1.get("a");
    int bval = ht1.get("b");
    std::cout << "aval = " << aval << " bval = " << bval << std::endl;
    /*HashMap<Coord, int> ht2;
    Coord c1(0, 0);
    Coord c2(4, 7);
    ht2.set(c1, 10);
    ht2.set(c2, 20);
    int aaval = ht2.get(c1);
    int bbval = ht2.get(c2);
    std::cout << "aaval = " << aaval << " bbval = " << bbval << std::endl;
    */

    return 0;
}







