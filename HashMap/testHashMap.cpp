#include <iostream>
#include <vector>
#include <cassert>
#include "HashMap.h"
#include "../Coord/Coord.h"
void testGetterSetter()
{
    std::cout << "\n<------ Testing getter and setter ------> \n";
    HashMap<std::string, int> map;
    map.insert("key1", 1);
    map.insert("key2", 2);
    int val1 = map["key1"];
    int val2 = map["key2"];
    assert(val1 == 1);
    assert(val2 == 2);
    bool caughtException = false;
    try {
        int val3 = map["key3"];
        (void) val3;
    } catch (std::logic_error) {
        caughtException = true;
    }
    assert(caughtException);

}

void testRemove()
{
    std::cout << "\n<------ Testing remove ------> \n";
    HashMap<std::string, int> map;
    map.insert("key", 1);
    map.remove("key");
    bool caughtException = false;
    try {
        int val = map["key"];
        (void) val;
    } catch (std::logic_error) {
        caughtException = true;
    }
    assert(caughtException);

}

void testIterator1()
{
    std::cout << "\n<------ Testing iterator ------> \n";
    HashMap<std::string, int> map;
    int values[3] = {1, 2, 3};
    map.insert("key1", 1);
    map.insert("key2", 2);
    map.insert("key3", 3);
    int j = 0;
    for (HashMap<std::string, int>::iterator it = map.begin(); 
         it != map.end(); ++it) {
        assert(it.value() == values[j]);
        j++;
    }
}
void testIterator2()
{
    HashMap<Coord, int> map;
    std::vector<int> values;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Coord c(i, j);
            values.push_back(i + j);
            map.insert(c, i + j);
        }
    }
    int j = 0;
    for (HashMap<Coord, int>::iterator it = map.begin(); 
         it != map.end(); ++it) {
        assert(it.value() == values[j]);
        j++;
    }

}
void testType()
{
    std::cout << "\n<------ Testing using custum defined object ------> \n";
    HashMap<Coord, int> map;
    Coord c1(1, 2);
    Coord c2(2, 3);
    Coord c3(3, 4);
    map.insert(c1, 10);
    map.insert(c2, 20);
    int val1 = map[c1];
    int val2 = map[c2];
    assert(val1 == 10);
    assert(val2 == 20);

}
void testConstructor()
{
    std::cout << "\n<------ Testing constructor ------> \n";
    HashMap<Coord, int> map1;
    size_t size = 200;
    HashMap<std::string, int> map2(size);
}
int main()
{
    std::cout << "============== Running tests for Hash Map ==============\n";
    testConstructor();
    testGetterSetter();
    testRemove();
    testType();
    testIterator1();
    testIterator2();
    std::cout << "============== Tests for HashMap completed! ==============\n";
}







