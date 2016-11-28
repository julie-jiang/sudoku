CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: Soduku_Driver.o Sodukupp.o Parser.o
	${CXX} ${CXXFLAGS} Soduku_Driver.cpp Soduku.cpp Coord/Coord.cpp Soduku_Parser.cpp -o soduku

test: Soduku_Tester.o
	${CXX} ${CXXFLAGSS} Soduku_Tester.cpp -o test_soduku

Soduku_Driver.o: Soduku_Driver.cpp 
Sodukupp.o: Soduku.cpp
Parser.o: Soduku_Parser.cpp
Soduku_Tester.o: Soduku_Tester.cpp

.PHONY: soduku