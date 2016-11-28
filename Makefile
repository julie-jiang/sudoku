CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: sodukuSolver.o Sodukupp.o
	${CXX} ${CXXFLAGS} sodukuSolver.cpp Soduku.cpp Coord/Coord.cpp -o soduku

sodukuSolver.o: sodukuSolver.cpp 
Sodukupp.o: Soduku.cpp

.PHONY: soduku