/* 
   testCoord.cpp
   Unit tests for the class Coord.
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* To compile the test program, use the Makefile in this directory and run: 
        ./testCoord
   This tests all the functionality of the class Coord, including all the 
   corner cases I could think of. Testing is done using assertion, so all tests
   are passed if the program correctly terminates. */
#include <iostream>
#include <sstream>
#include <cassert>
#include "Coord.h"
#include "../Set/Set.h"

void testConstructor()
{
    std::cout <<"Testing constructor...";
    Coord c1(1, 2);
    std::cout << "test passed.\n";
}
void testSubscript()
{
    std::cout << "Testing Subscript operator...";
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
void testCout()
{
    std::cout << "Testing ostream operator ...";
    Coord c1(1, 2);
    std::stringstream buffer;
    buffer << c1;
    assert(buffer.str() == "(1, 2)");
    std::cout <<"test passed.\n";
}

int main()
{
    std::cout << "======Running tests for Coord======\n";
    testConstructor();
    testSubscript();
    testEqual();
    testGreaterThan();
    testGEQ();
    testSmallerThan();
    testLEQ();
    testCout();
    std::cout << "======All tests passed!======\n";

}