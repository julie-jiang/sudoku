CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: sodukuSolver.o Soduku.o
	${CXX} ${CXXFLAGS} sodukuSolver.cpp Soduku.cpp -o sodukuit
AVLTree: testAVLTree.o 
	${CXX} ${CXXFLAGS} testAVLTree.cpp -o testAVLTree
HashTable: testHashTable.o
	${CXX} ${CXXFLAGS} testHashTable.cpp Coord.cpp -o testHashTable
Coord: testCoord.o Coord.o
	${CXX} ${CXXFLAGS} testCoord.cpp Coord.cpp -o testCoord


sodukuSolver.o: sodukuSolver.cpp Soduku.h
Soduku.o: Soduku.cpp Soduku.h
testAVLTree.o: testAVLTree.cpp AVLTree.h
testHashTable.o: testHashTable.cpp HashTable.h Coord.h
testCoord.o: testCoord.cpp Coord.h AVLTree.h
Coord.o: Coord.cpp Coord.h