#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <stack>
#include "Set.h"
#include "../Coord/Coord.h"

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
    std::cout << "Testing add function...";
    testAdd1(); // Left left unbalance 
    testAdd2(); // Left right unbalance
    testAdd3(); // Right right unbalance
    testAdd4(); // Right left unbalance
    testAdd5(); // Adding duplicates
    std::cout << "test passed\n";
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

void testRemove7()
{
    Set<Coord> *set = new Set<Coord>;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            Coord c(i, j);
            set->add(c);
        }
    }

    std::vector<Coord> v;
    for (Set<Coord>::iterator it = set->begin(); it != set->end(); ++it) {
        v.push_back(*it);
    }
    
    for (size_t i = 0; i < v.size(); i++) {
        //std::cout << "Removing " << v[i] << " \n";
        set->remove(v[i]);
    } std::cout << "\n";
    std::cout << *set << "\n";
}
void testRemove()
{
    std::cout << "Testing function remove...  ";
    testRemove1();
    testRemove2();
    testRemove3();
    testRemove4();
    //testRemove7();
    std::cout << "test passed\n";

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
    assert(buffer.str() == "[-1, 0, 1, 2, 5, 6, 9, 10, 11]");
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
void testCout1()
{
    Set<int> set;
    set.add(9); set.add(5); set.add(10);
    std::stringstream buffer;
    buffer << set;
    assert(buffer.str() == "[5, 9, 10]");
    
}
void testCout2()
{
    Set<int> set;
    std::stringstream buffer;
    buffer << set;
    assert(buffer.str() == "[]");
}
void testCout()
{
    std::cout << "Testing standard cout...";
    testCout1();
    testCout2();

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
