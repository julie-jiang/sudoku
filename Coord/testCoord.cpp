#include <iostream>
#include "Coord.h"
#include "../AVLTree/AVLTree.h"
#include <cstdlib>
#include <map>

int main()
{
    Coord c1(2, 3);
    Coord c2(2, 3);
    Coord c3(1, 1);
    int a = c1[0];
    int b = c2[1];
    std::cout << "a = " << a << " b = " << b << std::endl;
    if (c1 == c2) {
        std::cout << "c1 == c2\n";
    } else {
        std::cout << "c1 != c2\n";
    }
    if (c1 == c3) {
        std::cout << "c1 == c3\n";
    } else {
        std::cout << "c1 != c3\n";
    }

    std::cout << c1 << std::endl;

    /*std::map<Coord, AVLTree<int>> mymap;
    mymap.insert(std::pair<Coord, AVLTree<int>>(c1, AVLTree<int>()));*/
    /*std::map<Coord, int> mymap2;
    mymap2.insert(std::pair<Coord, int>(c1, 10));*/

}