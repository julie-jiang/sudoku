CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: Soduku_Main.cpp
	${CXX} ${CXXFLAGS} Soduku_Driver.cpp Soduku.cpp Coord/Coord.cpp \
					   Soduku_Parser.cpp Soduku_Solver.cpp Soduku_Checker.cpp \
					   Soduku_Generator.cpp Soduku_Util.cpp Soduku_Main.cpp \
					   -o soduku

test: Soduku_Tester.cpp
	${CXX} ${CXXFLAGS} Soduku_Tester.cpp Soduku.cpp Coord/Coord.cpp \
	                   Soduku_Driver.cpp Soduku_Solver.cpp Soduku_Checker.cpp \
	                   Soduku_Util.cpp Soduku_Generator.cpp -o test_soduku

generator: Soduku_Generator.cpp
	${CXX} ${CXXFLAGS} Soduku_Generator.cpp Soduku.cpp Coord/Coord.cpp \
					   generator.cpp Soduku_Util.cpp -o generate


.PHONY: soduku