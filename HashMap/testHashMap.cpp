#include <iostream>
#include <vector>
#include <cassert>
#include "HashMap.h"
#include "../Coord/Coord.h"
#include "../Set/Set.h"
void testGetterSetter()
{
    std::cout << "Testing getter and setter...";
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
    std::cout << "test passed.\n";
}

void testRemove()
{
    std::cout << "Testing remove...";
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
    std::cout << "test passed.\n";

}

void testIterator1()
{
    std::cout << "Testing iterator...";
    HashMap<std::string, int> map;
    int values[3] = {3, 2, 1};
    std::string keys[3] = {"key3", "key2", "key1"};
    map.insert("key1", 1);
    map.insert("key2", 2);
    map.insert("key3", 3);
    int j = 0;
    
    for (HashMap<std::string, int>::key_iterator k = map.begin(); 
         k != map.end(); ++k) {
        assert(*k == keys[j]);
        assert(map[*k] == values[j]);
        j++;
    }

    
}
void testIterator2()
{
    HashMap<Coord, int> map;
    Coord c1(1, 2);
    Coord c2(2, 3);
    Coord c3(3, 4);
    map.insert(c1, 10);
    map.insert(c2, 20);
    map.insert(c3, 30);
    for (HashMap<Coord, int>::key_iterator k = map.begin(); 
         k != map.end(); ++k) {
        std::cout << *k << std::endl;
    }
    std::cout << "test passed.\n";
}

void testType1()
{
    std::cout << "Testing using custum defined object...";
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
void testType2()
{
    HashMap<int, Coord> map;
    Coord c1(1, 2);
    Coord c2(2, 3);
    map.insert(10, c1);
    map.insert(20, c2);
    Coord val1 = map[10];
    Coord val2 = map[20];
    assert(val1 == c1);
    assert(val2 == c2);

}
void testType3()
{
    HashMap<Coord, Set<int>> map;
    Coord c(1, 2);
    map.insert(c, Set<int>());
    for (int i = 0; i < 10; i++) {
        map[c].add(i);
    }
    for (HashMap<Coord, Set<int>>::key_iterator it = map.begin(); 
         it != map.end(); ++it) {
        assert(*it == c);
    }
    std::cout << "test passed.\n";
}
void testConstructor()
{
    std::cout << "Testing constructor...";
    HashMap<Coord, int> map1;
    size_t size = 200;
    HashMap<std::string, int> map2(size);
    std::cout << "test passed.\n";
}
void testCopyConstructor()
{
    std::cout << "Testing copy constructor...";
    HashMap<std::string, int> map1;
    map1.insert("key1", 10);
    map1.insert("key2", 20);
    HashMap<std::string, int> map2(map1);
    assert(map2["key1"] == map1["key1"]);
    assert(map2["key2"] == map1["key2"]);
    std::cout << "test passed.\n";
}
int main()
{
    std::cout << "============== Running tests for Hash Map ==============";
    testConstructor();
    testCopyConstructor();
    testGetterSetter();
    testRemove();
    testType1();
    testType2();
    testType3();
    testIterator1();
    testIterator2();

    std::cout << "============== Tests for HashMap completed! ==============";
}







