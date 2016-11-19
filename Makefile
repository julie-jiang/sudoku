CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: sodukuSolver.o Soduku.o
	${CXX} ${CXXFLAGS} sodukuSolver.cpp Soduku.cpp -o sodukuit

sodukuSolver.o: sodukuSolver.cpp Soduku.h
Soduku.o: Soduku.cpp Soduku.h

