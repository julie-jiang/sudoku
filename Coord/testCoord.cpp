#include <iostream>
#include "Coord.h"
#include "../AVLTree/AVLTree.h"
#include <cstdlib>
#include <map>
#include <cassert>
void testConstructor()
{
    std::cout <<"Testing constructor...";
    Coord c1(1, 2);
    std::cout << "test passed.\n";
}
void testGetSet()
{
    std::cout << "Testing getter and setter...";
    Coord c(2, 3);
    int a = c[0];
    int b = c[1];
    assert(a == 2);
    assert(b == 3);
    std::cout <<"test passed.\n";
}
void testEqual()
{
    std::cout << "Testing '==' and '!=' operators...";
    Coord c1(2, 3);
    Coord c2(1, 2);
    Coord c3(2, 3);
    assert(c1 == c3);
    assert(not (c2 == c3));
    assert(c1 != c2);
    assert(not (c1 != c3));
    std::cout <<"test passed.\n";
}
void testGreaterThan()
{
    std::cout << "Testing '>' operator...";
    Coord c1(1, 2);
    Coord c2(2, 1);
    Coord c3(2, 3);
    Coord c4(2, 3);
    assert(not (c1 > c2));
    assert(not (c2 > c3));
    assert(not (c3 > c4));
    assert(not (c4 > c3));
    assert(c3 > c2);
    assert(c2 > c1);
    std::cout <<"test passed.\n";

}
void testGEQ()
{
    std::cout << "Testing '>=' operator...";
    Coord c1(1, 2);
    Coord c2(2, 1);
    Coord c3(2, 3);
    Coord c4(2, 3);
    assert(not (c1 >= c2));
    assert(not (c2 >= c3));
    assert(c3 >= c4);
    assert(c4 >= c3);
    assert(c3 >= c2);
    assert(c2 >= c1);
    std::cout <<"test passed.\n";

}
void testSmallerThan()
{
    std::cout << "Testing '<' operator...";
    Coord c1(1, 2);
    Coord c2(2, 1);
    Coord c3(2, 3);
    Coord c4(2, 3);
    assert(c1 < c2);
    assert(c2 < c3);
    assert(not (c3 < c4));
    assert(not (c4 < c3));
    assert(not (c3 < c2));
    std::cout <<"test passed.\n";
}
void testLEQ()
{
    std::cout << "Testing '<=' operator...";
    Coord c1(1, 2);
    Coord c2(2, 1);
    Coord c3(2, 3);
    Coord c4(2, 3);
    assert(c1 <= c2);
    assert(c2 <= c3);
    assert(c3 <= c4);
    assert(c4 <= c3);
    assert(not (c3 <= c2));
    std::cout <<"test passed.\n";
}


int main()
{
    std::cout << "-----Running tests for Coord-----\n";
    testConstructor();
    testGetSet();
    testEqual();
    testGreaterThan();
    testGEQ();
    testSmallerThan();
    testLEQ();
    Coord c1(1, 2);
    std::map<Coord, AVLTree<int>> mymap;
    mymap.insert(std::pair<Coord, AVLTree<int>>(c1, AVLTree<int>()));
    /*std::map<Coord, int> mymap2;
    mymap2.insert(std::pair<Coord, int>(c1, 10));*/
    std::cout << "-----All tests passed!----\n";

}