#include <iostream>
#include <vector>
#include <cassert>
#include "LinkedList.h"
#include "../../Coord/Coord.h"
#include "../../Set/Set.h"

void testIterator()
{
    std::cout << "\nTesting iterator  \n";
    LinkedList<Coord, int> list;
    std::vector<int> values;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Coord c(i, j);
            values.push_back(i + j);
            list.insert(c, i + j);
        }
    }
    int i = 0;
    for (LinkedList<Coord, int>::iterator it = list.begin(); it != list.end(); ++it) {
        Coord c = it.key();
        assert(it.value() == values[i]);
        i++;
    }
    // Empty list
    LinkedList<Coord, int> list2;
    for (LinkedList<Coord, int>::iterator it = list2.begin(); it != list2.end(); ++it) {
        assert(false);
    }
}
void testType1()
{
    std::cout << "\nTesting using customly defined object  \n";
    LinkedList<Coord, int> list;
    Coord c1(0, 0);
    Coord c2(4, 7);
    list.insert(c1, 10);
    list.insert(c2, 20);
    int val1 = list[c1];
    int val2 = list[c2];
    assert(val1 = 10);
    assert(val2 = 20);
}
void testType2()
{
    LinkedList<std::string, Set<int>> list;
    list.insert("key", Set<int>());
    for (int i = 0; i < 10; i++) {
        list["key"].add(i);
    }
    for (LinkedList<std::string, Set<int>>::iterator it = list.begin();
         it != list.end(); ++it) {
        assert(it.key() == "key");
        assert(it.value().size() == 10);
    }
}
void testGetterSetter1()
{
    std::cout << "\nTesting getter and setter  \n";
    LinkedList<std::string, int> list;
    
    list.insert("key1", 1);
    list.insert("key2", 1);
    list.insert("key2", 2);
    
    int val1 = list["key1"];
    int val2 = list["key2"];
    assert(val1 = 1);
    assert(val2 = 2);
    assert(list.size() == 2);
    bool caught_exception = false;
    try {
        int val3 = list["key3"];
        (void) val3;
    } catch (std::logic_error) {
        caught_exception = true;
    }
    assert(caught_exception);

}
void testGetterSetter2()
{
    LinkedList<std::string, int> list;
    bool caught_exception = false;
    try {
        int val = list["key"];
        (void) val;
    } catch (std::logic_error) {
        caught_exception = true;
    }
    assert(caught_exception);
}

void testRemove1()
{
    std::cout << "\nTesting function remove  \n";
    LinkedList<std::string, int> list;
    list.insert("key1", 2);
    list.insert("key1", 1);
    list.insert("key2", 1);
    list.insert("key3", 2);
    assert(list.remove("key2"));
    assert(not list.remove("key4"));
    assert(list.remove("key1"));
    assert(list.size() == 1);
    LinkedList<std::string, int>::iterator it = list.begin();
    assert(it.key() == "key3");
    assert(it.value() == 2);
}
void testRemove2()
{
    LinkedList<std::string, int> list;
    list.insert("key1", 1);
    list.insert("key2", 2);
    list.insert("key3", 3);
    list.insert("key4", 4);
    assert(list.remove("key1"));
    assert(list.size() == 3);
    assert(list.remove("key2"));
    assert(list.size() == 2);
    assert(list.remove("key3"));
    assert(list.size() == 1);
    LinkedList<std::string, int>::iterator it = list.begin();
    assert(it.key() == "key4");
    assert(it.value() == 4);
}

void testEmpty()
{
    std::cout << "\nTesting function empty  \n";
    
    LinkedList<std::string, int> list;
    assert(list.empty());
    list.insert("key1", 1);
    assert(not list.empty());

}

void testSize()
{
    std::cout << "\nTesting function size  \n";
    
    LinkedList<std::string, int> list;
    assert(list.size() == 0);
    list.insert("key1", 1);
    assert(list.size() == 1);
    list.insert("key1", 2);
    assert(list.size() == 1);
    assert(list["key1"] == 2);

}
void testPointer()
{
    LinkedList<int, int> *list = new LinkedList<int, int>;
    list->insert(1, 10);
    list->insert(2, 20);
    int val1 = (*list)[1];
    int val2 = (*list)[2];
    assert(val1 == 10);
    assert(val2 == 20);
    delete list;
}
int main()
{
    std::cout << "============== Running tests for LinkedList ==============\n";
    
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
    std::cout << "============== Tests for LinkedList completed! ==============\n";
	

	

}