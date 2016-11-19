#include <iostream>
#include <cstdlib>
#include <stack>
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

void testRemove1()
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

void testRemove2()
{
    AVLTree<int> *avl = new AVLTree<int>;
    for (int i = 1; i < 10; i++) {
        avl->add(i);
    }
    avl->remove(9);
    avl->remove(6);
    avl->remove(3);
    avl->remove(1);
    avl->remove(2);
    std::cout << "Output should be: [4 5 7 8 ]\n";
    std::cout << "Actual output:    ";
    avl->print();
    std::cout << std::endl;
    delete avl;
}
void testRemove3()
{
    AVLTree<int> *avl = new AVLTree<int>;
    for (int i = 1; i < 10; i++) {
        avl->add(i);
    }
    avl->printTree();
    avl->remove(9); avl->printTree();
    avl->remove(7); avl->printTree();
    avl->remove(8); avl->printTree();
    avl->remove(6); avl->printTree();
    avl->remove(3); avl->printTree();
    avl->remove(1);avl->printTree();
    avl->remove(2);avl->printTree();
    std::cout << "Output should be: [4 5 ]\n";
    std::cout << "Actual output:    ";
    avl->print();
    std::cout << std::endl;
    delete avl;

}
void testRemove()
{
    std::cout << "\n<------ Testing function remove ------> \n";
    //testRemove1();
    //testRemove2();
    testRemove3();

}


void testGetElements()
{
    std::cout << "\n<------ Testing function getElements ------> \n";
    AVLTree<int> *avl = new AVLTree<int>;
    std::cout << "Output should be \n";
    avl->add(9);  avl->add(5); avl->add(10);
    avl->add(0);  avl->add(6); avl->add(11);
    avl->add(-1); avl->add(1); avl->add(2);

    std::stack<int> intStack = avl->getElements();
    while (not intStack.empty()) {
        std::cout << intStack.top() << " ";
        intStack.pop();
    }
    std::cout << std::endl;

}
void testSize()
{
    std::cout << "\n<------ Testing function size------> \n";
    std::cout << "Output should be: 0 1 9\n";
    std::cout << "Actual output:    ";
    AVLTree<int> *avl1 = new AVLTree<int>;
    std::cout << avl1->size() << " ";
    AVLTree<int> *avl2 = new AVLTree<int>;
    AVLTree<int> *avl3 = new AVLTree<int>;
    avl2->add(2);
    std::cout << avl2->size() << " ";
    avl3->add(9);  avl3->add(5); avl3->add(10);
    avl3->add(0);  avl3->add(6); avl3->add(11);
    avl3->add(-1); avl3->add(1); avl3->add(2);
    std::cout << avl3->size() << " " << std::endl;
    
    delete avl1;
    delete avl2;
    delete avl3;


}


int main() 
{
    std::cout << "============== Running tests for AVLTree ==============\n";
    testAdd();
    testContains();
    testRemove();
    testGetElements();
    testSize();
    std::cout << "============== Tests for AVLTree completed! ==============\n";
}
