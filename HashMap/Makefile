CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

HashMap: testHashMap.o
	${CXX} ${CXXFLAGS} testHashMap.cpp ../Coord/Coord.cpp -o testHashMap

testMap.o: testHashMap.cpp 