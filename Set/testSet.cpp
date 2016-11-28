#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <stack>
#include "Set.h"
#include "../Coord/Coord.h"


void testAddLeftLeft()
{
    Set<int> *set = new Set<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 []] 30 [[[] 40 []] 50 [[] 60 []]]] \n"; 
    set->add(60); set->add(50); set->add(30);
    set->add(20); set->add(40); set->add(10);
    std::cout << "Actual output:    ";
    set->printTree();
    delete set;

}
void testAddLeftRight()
{

    Set<int> *set = new Set<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 [[] 30 []]] 40 [[] 50 [[] 60 []]]] \n"; 
    set->add(60); set->add(20); set->add(50);
    set->add(10); set->add(40); set->add(30);
    std::cout << "Actual output:    ";
    set->printTree();
    delete set;

}
void testAddRightRight()
{
    Set<int> *set = new Set<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 [[] 30 []]] 40 [[] 50 [[] 60 []]]] \n"; 
    set->add(10); set->add(20); set->add(40);
    set->add(30); set->add(50); set->add(60);
    std::cout << "Actual output:    ";
    set->printTree();
    delete set;
}
void testAddRightLeft()
{
    Set<int> *set = new Set<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 []] 30 [[[] 40 []] 50 [[] 60 []]]] \n"; 
    set->add(10); set->add(50); set->add(20);
    set->add(30); set->add(60); set->add(40);
    std::cout << "Actual output:    ";
    set->printTree();
    delete set;
}
void testAddDuplicates()
{
    Set<int> *set = new Set<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 []] 30 [[[] 40 []] 50 [[] 60 []]]] \n"; 
    set->add(10); set->add(50); set->add(20);
    set->add(30); set->add(60); set->add(40);
    set->add(30); set->add(50); set->add(10);
    std::cout << "Actual output:    ";
    set->printTree();
    delete set;

}
void testAdd()
{
    std::cout << "Testing add function...\n";
    testAddLeftLeft();
    testAddLeftRight();
    testAddRightRight();
    testAddRightLeft();
    testAddDuplicates();
}
/*
 * Tests contains when
 *      (1) The value being searched for is the root of the tree
 *      (2) The value being searched for has two children
 *      (3) The value being searched for has one child
 *      (4) The value being searched for has no children
 *      (5) The value being searched for does not exist
 */
void testContains() 
{
    std::cout << "Testing function contains...";
    Set<int> *set = new Set<int>;
    set->add(10); set->add(50); set->add(20);
    set->add(30); set->add(60); set->add(40);
    assert(set->contains(30)); // Case 1
    assert(set->contains(50)); // Case 2
    assert(set->contains(20)); // Case 3
    assert(set->contains(10)); // Case 4
    assert(not set->contains(70)); // Case 5
    std::cout << "test passed.\n";
    delete set;
}

void testRemove1()
{
    Set<int> *set = new Set<int>;
    std::cout << "Output should be: [[[[] -1 []] 0 []] 1 [[[[] 2 []] 5 [[] 6 []]] 9 [[] 11 []]]]\n";
    set->add(9);  set->add(5); set->add(10);
    set->add(0);  set->add(6); set->add(11);
    set->add(-1); set->add(1); set->add(2);
    set->remove(10);
    std::cout << "Actual output:    ";
    set->printTree();
    delete set;
}

void testRemove2()
{
    Set<int> *set = new Set<int>;
    for (int i = 1; i < 10; i++) {
        set->add(i);
    }
    set->remove(9);
    set->remove(6);
    set->remove(3);
    set->remove(1);
    set->remove(2);
    std::stringstream buffer;
    buffer << *set;
    assert(buffer.str() == "[4 5 7 8 ]");
    delete set;
}
void testRemove3()
{
    Set<int> *set = new Set<int>;
    for (int i = 1; i < 10; i++) {
        set->add(i);
    }
    set->remove(9); 
    set->remove(7); 
    set->remove(8); 
    set->remove(6); 
    set->remove(3); 
    set->remove(1);
    set->remove(2);
    std::stringstream buffer;
    buffer << *set;
    assert(buffer.str() == "[4 5 ]");
    delete set;

}
void testRemove()
{
    std::cout << "Testing function remove...  \n";
    testRemove1();
    testRemove2();
    testRemove3();

}
void testSize()
{
    std::cout << "Testing function size...";
    Set<int> *set1 = new Set<int>;
    Set<int> *set2 = new Set<int>;
    Set<int> *set3 = new Set<int>;
    set2->add(2);
    set3->add(9);  set3->add(5); set3->add(10);
    set3->add(0);  set3->add(6); set3->add(11);
    set3->add(-1); set3->add(1); set3->add(2);
    assert(set1->size() == 0);
    assert(set2->size() == 1);
    assert(set3->size() == 9);
    
    delete set1;
    delete set2;
    delete set3;
    std::cout << "...test passed\n";
}

void testIterator()
{
    std::cout << "Testing iterator...";
    Set<int> set;
    set.add(9);  set.add(5); set.add(10);
    set.add(0);  set.add(6); set.add(11);
    set.add(-1); set.add(1); set.add(2);
    Set<int> set2(set);
    std::stringstream buffer;
    for (Set<int>::iterator i = set2.begin(); i != set2.end(); ++i)
    {
        buffer << *i << " ";
    }
    assert(buffer.str() == "11 10 9 6 5 2 1 0 -1 ");
    std::cout << "...test passed\n";
    
}
void testCopyConstructor()
{
    std::cout << "Testing copy constructor ";
    Set<int> *set = new Set<int>;
    set->add(9);  set->add(5); set->add(10);
    set->add(0);  set->add(6); set->add(11);
    set->add(-1); set->add(1); set->add(2);
    Set<int> *set2 = new Set<int>(*set);
    std::stringstream buffer;
    buffer << *set2;
    assert(buffer.str() == "[-1 0 1 2 5 6 9 10 11 ]");
    std::cout << "...test passed\n";
    
}
void testType()
{
    std::cout << "Testing using Set with custom defined object...";
    Set<Coord> *set = new Set<Coord>;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            Coord c(i, j);
            set->add(c);
        }
    }
    Set<Coord> *set2 = new Set<Coord>(*set);
    delete set;
    delete set2;
    std::cout << "...test passed\n";
}

void testCout()
{
    std::cout << "Testing standard cout...";
    Set<int> set;
    set.add(9); set.add(5); set.add(10);
    std::stringstream buffer;
    buffer << set;
    assert(buffer.str() == "[5 9 10 ]");
    std::cout << "...test passed\n";
}


int main() 
{
    std::cout << "============== Running tests for Set ==============\n";
    testAdd();
    testContains();
    testRemove();
    testSize();
    testIterator();
    testCopyConstructor();
    testType();
    testCout();
    std::cout << "============== Tests for Set completed! ==============\n";
}
