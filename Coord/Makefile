# Makefile for the test program for Coord 

# By:   Julie Jiang
# UTLN: yjiang06
# Comp 15 Fall 2016 Independent Project

# To make the test program: make or make Coord
# To run the test program: ./testCoord

CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

Coord: testCoord.o 
	${CXX} ${CXXFLAGS} testCoord.cpp Coord.cpp -o testCoord

testCoord.o: testCoord.cpp Coord.h Coord.cpp 
