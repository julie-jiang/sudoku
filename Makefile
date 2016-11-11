CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: sodukuSolver.o Soduku.o
	${CXX} ${CXXFLAGS} sodukuSolver.cpp Soduku.cpp -o sodukuit
AVLTree: testAVLTree.o
	${CXX} ${CXXFLAGS} testAVLTree.cpp -o testAVLTree

sodukuSolver.o: sodukuSolver.cpp Soduku.h
Soduku.0: Soduku.cpp Soduku.h