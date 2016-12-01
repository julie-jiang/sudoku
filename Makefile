# Makefile for the main soduku program and the soduku test program

# By:   Julie Jiang
# UTLN: yjiang06
# Comp 15 Fall 2016 Independent Project

# To make the main program: make or make run_soduku
# To run the main program: ./run_soduku [other arguments]
# To make the test program: make test
# To run the test program: ./testSoduku

CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

run_soduku: Soduku/Soduku_Driver.o Soduku/Soduku.o Soduku/Soduku_Parser.o \
	    	Soduku/Soduku_Solver.o Soduku/Soduku_Checker.o Soduku_Main.o \
	    	Soduku/Soduku_Generator.o Soduku/Soduku_Util.o Set/Set.o \
			HashTable/HashTable.o Coord/Coord.o LinkedList/LinkedList.o
	${CXX} ${CXXFLAGS} Soduku/Soduku_Driver.cpp Soduku/Soduku.cpp \
					   Coord/Coord.cpp Soduku/Soduku_Parser.cpp \
					   Soduku/Soduku_Solver.cpp Soduku/Soduku_Checker.cpp \
					   Soduku/Soduku_Generator.cpp Soduku/Soduku_Util.cpp \
					   Soduku_Main.cpp -o run_soduku

test: Soduku_Tester.o Soduku/Soduku_Driver.o Soduku/Soduku.o Coord/Coord.o \
	  Soduku/Soduku_Parser.o Soduku/Soduku_Solver.o Soduku/Soduku_Checker.o \
      Soduku/Soduku_Generator.o Soduku/Soduku_Util.o 
	${CXX} ${CXXFLAGS} Soduku_Tester.cpp Soduku/Soduku.cpp Coord/Coord.cpp \
	                   Soduku/Soduku_Driver.cpp Soduku/Soduku_Solver.cpp \
	                   Soduku/Soduku_Checker.cpp Soduku/Soduku_Util.cpp \
	                   Soduku/Soduku_Generator.cpp -o test_soduku

Soduku/Soduku.o: Soduku/Soduku.cpp Soduku/Soduku.h
Soduku/Soduku_Solver.o: Soduku/Soduku_Solver.cpp Soduku/Soduku_Solver.h
Soduku/Soduku_Checker.o: Soduku/Soduku_Checker.cpp Soduku/Soduku_Checker.h 
Soduku/Soduku_Generator.o:Soduku/Soduku_Generator.cpp Soduku/Soduku_Generator.h
Soduku/Soduku_Driver.o: Soduku/Soduku_Driver.cpp Soduku/Soduku_Driver.h
Soduku/Soduku_Parser.o: Soduku/Soduku_Parser.cpp Soduku/Soduku_Parser.h
Soduku/Soduku_Util.o: Soduku/Soduku_Util.cpp Soduku/Soduku_Util.h
HashTable/HashTable.o: HashTable/HashTable.h HashTable/HTIterator.h
Coord/Coord.o: Coord/Coord.cpp Coord/Coord.h
Set/Set.o: Set/Set.h Set/SetNode.h Set/SetIterator.h
LinkedList/LinkedList.o: LinkedList/LinkedList.h LinkedList/ListIterator.h \
						 LinkedList/ListNode.h

.PHONY: run_soduku, test