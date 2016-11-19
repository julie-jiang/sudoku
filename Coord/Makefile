CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

Coord: testCoord.o Coord.o
	${CXX} ${CXXFLAGS} testCoord.cpp Coord.cpp -o testCoord

Coord.o: Coord.cpp Coord.h
testCoord.o: testCoord.cpp Coord.h 
