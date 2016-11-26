#include <iostream>
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
    std::cout << "\n<------ Testing add function ------> \n";
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
    std::cout << "\n<------ Testing function contains ------> \n";
    Set<int> *set = new Set<int>;
    set->add(10); set->add(50); set->add(20);
    set->add(30); set->add(60); set->add(40);
    // Case 1
    std::cout << "Output should be: 1\n";
    std::cout << "Actual output:    " << set->contains(30) << std::endl;
    // Case 2
    std::cout << "Output should be: 1\n";
    std::cout << "Actual output:    " << set->contains(50) << std::endl;
    // Case 3
    std::cout << "Output should be: 1\n";
    std::cout << "Actual output:    " << set->contains(20) << std::endl;
    // Case 4
    std::cout << "Output should be: 1\n";
    std::cout << "Actual output:    " << set->contains(10) << std::endl;
    // Case 5
    std::cout << "Output should be: 0\n";
    std::cout << "Actual output:    " << set->contains(70) << std::endl;
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
    std::cout << "Output should be: [4 5 7 8 ]\n";
    std::cout << "Actual output:    ";
    set->print();
    std::cout << std::endl;
    delete set;
}
void testRemove3()
{
    Set<int> *set = new Set<int>;
    for (int i = 1; i < 10; i++) {
        set->add(i);
    }
    set->printTree();
    set->remove(9); set->printTree();
    set->remove(7); set->printTree();
    set->remove(8); set->printTree();
    set->remove(6); set->printTree();
    set->remove(3); set->printTree();
    set->remove(1);set->printTree();
    set->remove(2);set->printTree();
    std::cout << "Output should be: [4 5 ]\n";
    std::cout << "Actual output:    ";
    set->print();
    std::cout << std::endl;
    delete set;

}
void testRemove()
{
    std::cout << "\n<------ Testing function remove ------> \n";
    testRemove1();
    testRemove2();
    testRemove3();

}
void testSize()
{
    std::cout << "\n<------ Testing function size------> \n";
    std::cout << "Output should be: 0 1 9\n";
    std::cout << "Actual output:    ";
    Set<int> *set1 = new Set<int>;
    std::cout << set1->size() << " ";
    Set<int> *set2 = new Set<int>;
    Set<int> *set3 = new Set<int>;
    set2->add(2);
    std::cout << set2->size() << " ";
    set3->add(9);  set3->add(5); set3->add(10);
    set3->add(0);  set3->add(6); set3->add(11);
    set3->add(-1); set3->add(1); set3->add(2);
    std::cout << set3->size() << " " << std::endl;
    
    delete set1;
    delete set2;
    delete set3;


}

void testIterator()
{
    std::cout << "\n<------ Testing iterator------> \n";
    Set<int> *set = new Set<int>;
    std::cout << "Output should be: 11 10 9 6 5 2 1 0 -1\n";
    std::cout << "Actual output:    ";
    set->add(9);  set->add(5); set->add(10);
    set->add(0);  set->add(6); set->add(11);
    set->add(-1); set->add(1); set->add(2);
    for (Set<int>::iterator i = set->begin(); i != set->end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    delete set;
    
}
void testCopyConstructor()
{
    std::cout << "\n<------ Testing copy constructor------> \n";
    Set<int> *set = new Set<int>;
    std::cout << "Output should be: [-1 0 1 2 5 6 9 10 11 ]\n";
    std::cout << "Actual output:    ";
    set->add(9);  set->add(5); set->add(10);
    set->add(0);  set->add(6); set->add(11);
    set->add(-1); set->add(1); set->add(2);
    Set<int> *set2 = new Set<int>(*set);
    set2->print();
    std::cout << std::endl;
    
}
void testType()
{
    std::cout << "\n<------ Testing using Set with custom defined object------> \n";
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
    std::cout << "============== Tests for Set completed! ==============\n";
}
