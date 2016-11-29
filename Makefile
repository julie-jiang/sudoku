CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: Soduku_Driver.o Soduku.o Parser.o
	${CXX} ${CXXFLAGS} Soduku_Driver.cpp Soduku.cpp Coord/Coord.cpp Soduku_Parser.cpp -o soduku

test: Soduku_Tester.o 
	${CXX} ${CXXFLAGS} Soduku_Tester.cpp Soduku.cpp Coord/Coord.cpp -o test_soduku

Soduku_Driver.o: Soduku_Driver.cpp 
Soduku.o: Soduku.cpp
Parser.o: Soduku_Parser.cpp
Soduku_Tester.o: Soduku_Tester.cpp

.PHONY: soduku