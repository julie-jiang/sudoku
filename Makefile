CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: sodukuSolver.o Soduku.o
	${CXX} ${CXXFLAGS} sodukuSolver.cpp Soduku.cpp -o sodukuit
AVLTree: testAVLTree.o 
	${CXX} ${CXXFLAGS} testAVLTree.cpp -o testAVLTree
HashTable: testHashTable.o
	${CXX} ${CXXFLAGS} testHashTable.cpp -o testHashTable

sodukuSolver.o: sodukuSolver.cpp Soduku.h
Soduku.o: Soduku.cpp Soduku.h
testAVLTree.o: testAVLTree.cpp AVLTree.h