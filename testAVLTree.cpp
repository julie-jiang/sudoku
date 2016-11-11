#include <iostream>
#include <cassert>
#include "AVLTree.h"


void testAddLeftLeft()
{
    AVLTree<int> *avl = new AVLTree<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 []] 30 [[[] 40 []] 50 [[] 60 []]]] \n"; 
    avl->add(60); avl->add(50); avl->add(30);
    avl->add(20); avl->add(40); avl->add(10);
    std::cout << "Actual output:    ";
    avl->printTree();
    delete avl;

}
void testAddLeftRight()
{

    AVLTree<int> *avl = new AVLTree<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 [[] 30 []]] 40 [[] 50 [[] 60 []]]] \n"; 
    avl->add(60); avl->add(20); avl->add(50);
    avl->add(10); avl->add(40); avl->add(30);
    std::cout << "Actual output:    ";
    avl->printTree();
    delete avl;

}
void testAddRightRight()
{
    AVLTree<int> *avl = new AVLTree<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 [[] 30 []]] 40 [[] 50 [[] 60 []]]] \n"; 
    avl->add(10); avl->add(20); avl->add(40);
    avl->add(30); avl->add(50); avl->add(60);
    std::cout << "Actual output:    ";
    avl->printTree();
    delete avl;
}
void testAddRightLeft()
{
    AVLTree<int> *avl = new AVLTree<int>;
    std::cout << "Output should be: [[[[] 10 []] 20 []] 30 [[[] 40 []] 50 [[] 60 []]]] \n"; 
    avl->add(10); avl->add(50); avl->add(20);
    avl->add(30); avl->add(60); avl->add(40);
    std::cout << "Actual output:    ";
    avl->printTree();
    delete avl;
}
void testAdd()
{
    std::cout << "\n<------ Testing add function ------> \n";
    testAddLeftLeft();
    testAddLeftRight();
    testAddRightRight();
    testAddRightLeft();
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
    AVLTree<int> *avl = new AVLTree<int>;
    avl->add(10); avl->add(50); avl->add(20);
    avl->add(30); avl->add(60); avl->add(40);
    // Case 1
    std::cout << "Output should be: 1\n";
    std::cout << "Actual output:    " << avl->contains(30) << std::endl;
    // Case 2
    std::cout << "Output should be: 1\n";
    std::cout << "Actual output:    " << avl->contains(50) << std::endl;
    // Case 3
    std::cout << "Output should be: 1\n";
    std::cout << "Actual output:    " << avl->contains(20) << std::endl;
    // Case 4
    std::cout << "Output should be: 1\n";
    std::cout << "Actual output:    " << avl->contains(10) << std::endl;
    // Case 5
    std::cout << "Output should be: 0\n";
    std::cout << "Actual output:    " << avl->contains(70) << std::endl;
    delete avl;
}
void testRemoveLeftLeft()
{
    AVLTree<int> *avl = new AVLTree<int>;
    std::cout << "Output should be: [[[[] -1 []] 0 []] 1 [[[[] 2 []] 5 [[] 6 []]] 9 [[] 11 []]]]\n";
    avl->add(9);  avl->add(5); avl->add(10);
    avl->add(0);  avl->add(6); avl->add(11);
    avl->add(-1); avl->add(1); avl->add(2);
    avl->remove(10);
    std::cout << "Actual output:    ";
    avl->printTree();
    delete avl;
    
}
void testRemove()
{
    std::cout << "\n<------ Testing function remove ------> \n";
    testRemoveLeftLeft();
}


int main() 
{
    std::cout << "============== Running tests for AVLTree ==============\n";
    testAdd();
    testContains();
    testRemove();
    testIterator();
    std::cout << "============== Tests for AVLTree completed! ==============\n";
}
