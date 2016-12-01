# Makefile for the test program for HashTable.

# By:   Julie Jiang
# UTLN: yjiang06
# Comp 15 Fall 2016 Independent Project

# To make the test program: make or make HashTable
# To run the test program: ./testHashTable
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

HashTable: testHashTable.o
	${CXX} ${CXXFLAGS} testHashTable.cpp ../Coord/Coord.cpp -o testHashTable

testMap.o: testHashTable.cpp HashTable.H HTIterator.h \
           ../LinkedList/LinkedList.h ../LinkedList/ListIterator.h \
           ../LinkedList/ListNode.h ../Coord/Coord.cpp ../Coord/Coord.h \
           ../Set/Set.h