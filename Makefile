CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra 

soduku: Soduku_Main.cpp
	${CXX} ${CXXFLAGS} Soduku/Soduku_Driver.cpp Soduku/Soduku.cpp \
					   Coord/Coord.cpp Soduku/Soduku_Parser.cpp \
					   Soduku/Soduku_Solver.cpp Soduku/Soduku_Checker.cpp \
					   Soduku/Soduku_Generator.cpp Soduku/Soduku_Util.cpp \
					   Soduku_Main.cpp -o run_soduku

test: Soduku_Tester.cpp
	${CXX} ${CXXFLAGS} Soduku_Tester.cpp Soduku/Soduku.cpp Coord/Coord.cpp \
	                   Soduku/Soduku_Driver.cpp Soduku/Soduku_Solver.cpp \
	                   Soduku/Soduku_Checker.cpp Soduku/Soduku_Util.cpp \
	                   Soduku/Soduku_Generator.cpp -o test_soduku

.PHONY: soduku