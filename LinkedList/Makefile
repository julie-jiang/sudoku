# Makefile for the test program for LinkedList.

# By:   Julie Jiang
# UTLN: yjiang06
# Comp 15 Fall 2016 Independent Project

# To make the test program: make or make LinkedList
# To run the test program: ./testLinkedList
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

LinkedList: testLinkedList.o
	${CXX} ${CXXFLAGS} testLinkedList.cpp ../Coord/Coord.cpp -o testLinkedList

testLinkedList.o: testLinkedList.cpp LinkedList.h ListNode.h \
                  ../Coord/Coord.cpp ../Set/Set.h ../Set/SetIterator.h \
                  ../Set/SetNode.h