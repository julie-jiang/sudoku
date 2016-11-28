CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: Soduku_Driver.o Sodukupp.o Parser.o
	${CXX} ${CXXFLAGS} Soduku_Driver.cpp Soduku.cpp Coord/Coord.cpp Parser.cpp -o soduku

Soduku_Driver.o: Soduku_Driver.cpp 
Sodukupp.o: Soduku.cpp
Parser.o: Parser.cpp

.PHONY: soduku