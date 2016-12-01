# Makefile for the test program for Set.

# By:   Julie Jiang
# UTLN: yjiang06
# Comp 15 Fall 2016 Independent Project

# To make the test program: make or make Set
# To run the test program: ./testSet

CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

Set: testSet.o 
	${CXX} ${CXXFLAGS} testSet.cpp ../Coord/Coord.cpp -o testSet
	
testSet.o: testSet.cpp ../Coord/Coord.cpp Set.h SetIterator.h SetNode.h