CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: sodukuSolver.o Sodukupp.o
	${CXX} ${CXXFLAGS} sodukuSolver.cpp Sodukupp.cpp Coord/Coord.cpp -o sodukuit

sodukuSolver.o: sodukuSolver.cpp Sodukupp.h
Sodukupp.o: Sodukupp.cpp Sodukupp.h

