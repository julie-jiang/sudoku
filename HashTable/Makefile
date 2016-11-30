CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

HashTable: testHashTable.o
	${CXX} ${CXXFLAGS} testHashTable.cpp ../Coord/Coord.cpp -o testHashTable

testMap.o: testHashTable.cpp 