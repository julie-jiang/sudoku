/* 
   testLinkedList.cpp
   Unit tests for the container LinkedList. 

   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Blurb                                     */
/*****************************************************************************/
/* To compile the test program, use the Makefile in this directory and run: 
        ./testLinkedList
   This tests all the functionality of the class LinkedList, including all the 
   corner cases I could think of. Testing is done using assertion, so all tests
   are passed if the program correctly terminates (they all passed).         */
#include <iostream>
#include <vector>
#include <cassert>
#include "LinkedList.h"
#include "../Coord/Coord.h"
#include "../Set/Set.h"
/* Tests iterator when list is empty and when list is not empty */
void testIterator() {
    std::cout << "Testing iterator...";
    LinkedList<Coord, int> list;
    std::vector<int> values;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Coord c(i, j);
            values.push_back(i + j);
            assert(list.insert(c, i + j));
        }
    }
    // Not empty
    int i = 0;
    for (LinkedList<Coord, int>::iterator it = list.begin(); 
        it != list.end(); ++it) {
        assert(it.value() == values[i]);
        i++;
    }
    // Empty list
    LinkedList<Coord, int> list2;
    for (LinkedList<Coord, int>::iterator it = list2.begin(); 
        it != list2.end(); ++it) {
        assert(false);
    }
    std::cout << "test passed.\n";
}
/* Tests using non-primitive types */
void testType1() {
    std::cout << "Testing using customly defined object...";
    LinkedList<Coord, int> list;
    Coord c1(0, 0);
    Coord c2(4, 7);
    assert(list.insert(c1, 10));
    assert(list.insert(c2, 20));
    int val1 = list[c1];
    int val2 = list[c2];
    assert(val1 = 10);
    assert(val2 = 20);
}
void testType2() {
    LinkedList<std::string, Set<int>> list;
    assert(list.insert("key", Set<int>()));
    for (int i = 0; i < 10; i++) {
        list["key"].add(i);
    }
    for (LinkedList<std::string, Set<int>>::iterator it = list.begin();
         it != list.end(); ++it) {
        assert(it.key() == "key");
        assert(it.value().size() == 10);
    }

    std::cout << "test passed.\n";
}
/* Tests insert function and subscript operators. Checks the following corner
   cases:
        (1) values to be inserted already exists
        (2) value should be returned by reference
        (3) exceptions are thrown when attempting to get the value of a 
            nonexistent key  */
void testGetterSetter1() {
    std::cout << "Testing getter and setter...";
    LinkedList<std::string, int> list;
    
    assert(list.insert("key1", 1));
    assert(list.insert("key2", 1));
    // Should return false because "key2" already exists
    assert(not list.insert("key2", 2));  
    
    int val1 = list["key1"];
    int val2 = list["key2"];
    assert(val1 = 1);
    assert(val2 = 2);
    // Value should changed because it was returned by reference
    val1 = 3;
    assert(list["key1"] = 3);           
    assert(list.size() == 2);

    // "key3" should not exist
    bool caught_exception = false;       
    try {
        int val3 = list["key3"];
        (void) val3;
    } catch (std::logic_error) {
        caught_exception = true;
    }
    assert(caught_exception);
}
void testGetterSetter2() {
    // list is empty
    LinkedList<std::string, int> list;
    bool caught_exception = false;
    try {
        int val = list["key"];
        (void) val;
    } catch (std::logic_error) {
        caught_exception = true;
    }
    assert(caught_exception);
    std::cout << "test passed.\n";
}
/* Tests remove function. */
void testRemove1() {
    std::cout << "Testing function remove...";
    LinkedList<std::string, int> list;
    assert(list.insert("key1", 2));
    assert(not list.insert("key1", 1));
    assert(list.insert("key2", 1));
    assert(list.insert("key3", 2));
    assert(list.remove("key2"));
    assert(not list.remove("key4")); // "key4" does not exist 
    assert(list.remove("key1"));
    assert(list.size() == 1);
    LinkedList<std::string, int>::iterator it = list.begin();
    assert(it.key() == "key3");
    assert(it.value() == 2);
}
void testRemove2() {
    LinkedList<std::string, int> list;
    assert(list.insert("key1", 1));
    assert(list.insert("key2", 2));
    assert(list.insert("key3", 3));
    assert(list.insert("key4", 4));
    assert(list.remove("key1"));
    assert(list.size() == 3);
    assert(list.remove("key2"));
    assert(list.size() == 2);
    assert(list.remove("key3"));
    assert(list.size() == 1);
    LinkedList<std::string, int>::iterator it = list.begin();
    assert(it.key() == "key4");
    assert(it.value() == 4);

    std::cout << "test passed.\n";
}
/* Tests function empty */
void testEmpty() {
    std::cout << "Testing function empty...";
    
    LinkedList<std::string, int> list;
    assert(list.empty());
    assert(list.insert("key1", 1));
    assert(not list.empty());

    std::cout << "test passed.\n";
}
/* Tests function size */
void testSize() {
    std::cout << "Testing function size...";
    
    LinkedList<std::string, int> list;
    assert(list.size() == 0);
    assert(list.insert("key1", 1));
    assert(list.size() == 1);
    assert(not list.insert("key1", 2));
    assert(list.size() == 1);
    assert(list["key1"] == 2);

    std::cout << "test passed.\n";
}
/* Tests using a pointer */
void testPointer() {
    std::cout << "Testing using a pointer to a linkedlist...";
    LinkedList<int, int> *list = new LinkedList<int, int>;
    assert(list->insert(1, 10));
    assert(list->insert(2, 20));
    int val1 = (*list)[1];
    int val2 = (*list)[2];
    assert(val1 == 10);
    assert(val2 == 20);
    delete list;

    std::cout << "test passed.\n";
}
int main() {
    std::cout << "============ Running tests for LinkedList ============\n";
    testSize();
    testEmpty();
    testGetterSetter1();
    testGetterSetter2();
    testType1();
    testType2();
    testIterator();
    testRemove1();
    testRemove2();
    testPointer();
    std::cout << "============ Tests for LinkedList completed! ============\n";
    

    

}