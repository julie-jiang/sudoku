/* 
   testSet.cpp
   Unit tests for the container Set, an ordered collection of unique elements. 

   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* To compile the test program, use the Makefile in this directory and run: 
        ./testSet 
   This tests all the functionality of the class Set, including all the 
   corner cases I could think of. Testing is done using assertion, so all tests
   are passed if the program correctly terminates. */
#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <stack>
#include "Set.h"
#include "../Coord/Coord.h"
/*****************************************************************************/
/*                                 Test Add                                  */
/*****************************************************************************/
/* The first four functions tests the four possible cases of unbalance that may
   arise from inserting an element into an AVL Tree. The last function tests 
   that inserting duplicated elements will not change the tree. */

/* Left left unbalance */
void testAdd1()
{
    Set<int> *set = new Set<int>;
    set->add(60); set->add(50); set->add(30);
    set->add(20); set->add(40); set->add(10);
    std::string solution = std::string("30\n")
                         + std::string("    50\n")
                         + std::string("        60\n")
                         + std::string("        40\n")
                         + std::string("    20\n")
                         + std::string("        10\n");
    assert(set->tree() == solution);

    delete set;

}
/* Left right unbalance */
void testAdd2()
{

    Set<int> *set = new Set<int>;
    set->add(60); set->add(20); set->add(50);
    set->add(10); set->add(40); set->add(30);
    std::string solution = std::string("40\n")
                         + std::string("    50\n")
                         + std::string("        60\n")
                         + std::string("    20\n")
                         + std::string("        30\n")
                         + std::string("        10\n");
    assert(set->tree() == solution);
    delete set;

}
/* Right right unbalance */
void testAdd3()
{
    Set<int> *set = new Set<int>;
    set->add(10); set->add(20); set->add(40);
    set->add(30); set->add(50); set->add(60);
    std::string solution = std::string("40\n")
                         + std::string("    50\n")
                         + std::string("        60\n")
                         + std::string("    20\n")
                         + std::string("        30\n")
                         + std::string("        10\n");
    assert(set->tree() == solution);
    delete set;
}
/* Right left unbalance */
void testAdd4()
{
    Set<int> *set = new Set<int>;
    set->add(10); set->add(50); set->add(20);
    set->add(30); set->add(60); set->add(40);
    std::string solution = std::string("30\n")
                         + std::string("    50\n")
                         + std::string("        60\n")
                         + std::string("        40\n")
                         + std::string("    20\n")
                         + std::string("        10\n");
    assert(set->tree() == solution);
    delete set;
}
/* testing adding duplicates */
void testAdd5()
{
    Set<int> *set = new Set<int>;
    set->add(10); set->add(50); set->add(20);
    set->add(30); set->add(60); set->add(40);
    set->add(30); set->add(50); set->add(10);
    std::string solution = std::string("30\n")
                         + std::string("    50\n")
                         + std::string("        60\n")
                         + std::string("        40\n")
                         + std::string("    20\n")
                         + std::string("        10\n");
    assert(set->tree() == solution);
    delete set;

}
void testAdd()
{
    std::cout << "Testing function add...";
    testAdd1(); // Left left unbalance 
    testAdd2(); // Left right unbalance
    testAdd3(); // Right right unbalance
    testAdd4(); // Right left unbalance
    testAdd5(); // Adding duplicates
    std::cout << "test passed\n";
}

/*****************************************************************************/
/*                                Test Remove                                */
/*****************************************************************************/
/* Similar to insertion, the first four functions tests the four possible cases
   of unbalance that may arise from removing an element from an AVL Tree. The 
   last function tests removing an element that doesn't exist in the tree. */

/* Left left unbalance*/
void testRemove1()
{
    Set<int> *set = new Set<int>;
    set->add(70); set->add(50); set->add(80);
    set->add(20); set->add(60); set->add(90);
    set->add(10); set->add(30); set->add(40);
    set->remove(80);
    std::string solution = std::string("30\n")
                         + std::string("    70\n")
                         + std::string("        90\n")
                         + std::string("        50\n")
                         + std::string("            60\n")
                         + std::string("            40\n")
                         + std::string("    20\n")
                         + std::string("        10\n");
    assert(set->tree() == solution);
    delete set;
}

/* Left right unbalance */
void testRemove2()
{
    Set<int> *set = new Set<int>;
    set->add(70); set->add(50); set->add(80);
    set->add(20); set->add(60); set->add(90);
    set->add(10); set->add(30); set->add(40);
    set->remove(10); set->remove(80);
    std::string solution = std::string("50\n")
                         + std::string("    70\n")
                         + std::string("        90\n")
                         + std::string("        60\n")
                         + std::string("    30\n")
                         + std::string("        40\n")
                         + std::string("        20\n");
    assert(set->tree() == solution);
    delete set;

}

/* Right right unbalance */
void testRemove3()
{
    Set<int> *set = new Set<int>;
    set->add(30); set->add(10); set->add(40);
    set->add(20); set->add(60); set->add(90);
    set->add(50); set->add(70); set->add(80);
    set->remove(10);
    std::string solution = std::string("60\n")
                         + std::string("    80\n")
                         + std::string("        90\n")
                         + std::string("        70\n")
                         + std::string("    30\n")
                         + std::string("        40\n")
                         + std::string("            50\n")
                         + std::string("        20\n");
    assert(set->tree() == solution);
    delete set;
}
/* Right left unbalance */
void testRemove4()
{
    Set<int> *set = new Set<int>;
    set->add(30); set->add(10); set->add(40);
    set->add(20); set->add(80); set->add(90);
    set->add(50); set->add(70); set->add(60);
    set->remove(80); set->remove(10);
    std::string solution = std::string("50\n")
                         + std::string("    70\n")
                         + std::string("        90\n")
                         + std::string("        60\n")
                         + std::string("    30\n")
                         + std::string("        40\n")
                         + std::string("        20\n");
    assert(set->tree() == solution);
    delete set;
}
/* Test removing something that doesn't exist */
void testRemove5()
{
    Set<int> *set = new Set<int>;
    set->add(30); set->add(10); set->add(40);
    set->add(20); set->add(80); set->add(90);
    set->add(50); set->add(70); set->add(60);
    set->remove(100); set->remove(1); set->remove(22);
    set->remove(80); set->remove(10); set->remove(78);
    std::string solution = std::string("50\n")
                         + std::string("    70\n")
                         + std::string("        90\n")
                         + std::string("        60\n")
                         + std::string("    30\n")
                         + std::string("        40\n")
                         + std::string("        20\n");
    assert(set->tree() == solution);
    delete set;
}


void testRemove()
{
    std::cout << "Testing function remove...  ";
    testRemove1(); // Left left unbalance 
    testRemove2(); // Left right unbalance 
    testRemove3(); // Right right unbalance
    testRemove4(); // Right left unbalance
    testRemove5(); // Remove nonexistent elements
    std::cout << "test passed\n";

}
/*****************************************************************************/
/*                             Test Contains                                 */
/*****************************************************************************/
/* Tests contains when the value being searched for ...
        (1) is the root of the tree
        (2) has two children
        (3) has one child
        (4) has no children
        (5) does not exist  */
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
/*****************************************************************************/
/*                                Test Size                                  */
/*****************************************************************************/
/* Tests the size function when the set ...
        (1) is empty
        (2) contains only one element
        (3) contains many elements  */
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
    assert(set1->size() == 0); // Case 1
    assert(set2->size() == 1); // Case 2
    assert(set3->size() == 9); // Case 3
    
    delete set1;
    delete set2;
    delete set3;
    std::cout << "...test passed\n";
}
/*****************************************************************************/
/*                              Test Iterator                                */
/*****************************************************************************/
/* Tests the iterator when the set is empty and when the set is not empty
   In the process, tests all the functionalities of an iterator: constructor, 
   comparison operators, and dereference operator. */
void testIterator()
{
    std::cout << "Testing iterator...";

    Set<int> *set = new Set<int>; 
    // Case 1
    assert(set->begin() == set->end()); 
    set->add(9);  set->add(5); set->add(10);
    set->add(0);  set->add(6); set->add(11);
    set->add(-1); set->add(1); set->add(2);
    std::stringstream buffer;
    for (Set<int>::iterator i = set->begin(); i != set->end(); ++i) {
        buffer << *i << " ";
    }
    //Case 2
    assert(buffer.str() == "11 10 9 6 5 2 1 0 -1 ");
    std::cout << "...test passed\n";
    delete set;  
}
/*****************************************************************************/
/*                      Test Copy Constructor                                */
/*****************************************************************************/
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
    assert(buffer.str() == "[-1, 0, 1, 2, 5, 6, 9, 10, 11]");
    std::cout << "...test passed\n";
    delete set;
    delete set2;
    
}
/*****************************************************************************/
/*                                Test Type                                  */
/*****************************************************************************/
/* Tests using Set to hold non-primitive types. Also tests that 
   the copy constructor works. */
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
    Set<Coord> *set2 = new Set<Coord>(*set); // test copy constructor 
    delete set;
    delete set2;
    std::cout << "...test passed\n";
}
/*****************************************************************************/
/*                                Test OStream                               */
/*****************************************************************************/
/* Tests using the ostream operator "<<" when the set is empty and when the
   set it not empty */
void testOStream()
{
    Set<int> set;
    std::stringstream buffer;
    buffer << set;
    assert(buffer.str() == "[]");  // Empty set 
    set.add(9); set.add(5); set.add(10);
    buffer.str("");
    buffer.clear();
    buffer << set;
    assert(buffer.str() == "[5, 9, 10]"); // Nonempty set
    
}

int main() 
{
    std::cout << "============== Running tests for Set ==============\n";
    testAdd();
    testRemove();
    testContains();
    testSize();
    testIterator();
    testCopyConstructor();
    testType();
    std::cout << "============== Tests for Set completed! ==============\n";
}
