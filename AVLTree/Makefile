CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

AVLTree: testAVLTree.o 
	${CXX} ${CXXFLAGS} testAVLTree.cpp ../Coord/Coord.cpp -o testAVLTree
	
testAVLTree.o: testAVLTree.cpp ../Coord/Coord.cpp