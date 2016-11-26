CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

LinkedList: testLinkedList.o
	${CXX} ${CXXFLAGS} testLinkedList.cpp ../Coord/Coord.cpp -o testLinkedList

testLinkedList.o: testLinkedList.cpp LinkedList.h ListNode.h