#ifndef SODUKU_H
#define SODUKU_H
#include <cstdlib>
#include <queue>
#include <map>
#include "AVLTree.h"

class Soduku {

public:
	Soduku(std::string, int);
	~Soduku();

private:
	int gridSize;
	typedef std::pair<int, int> Coord;
	std::map<Coord, AVLTree<int>> grid;

	std::queue<Coord> Queue;

	int string2int(std::string);
	void printGrid();
	void arcConsistency();
	bool validateDomain(Coord);
	bool valueIsInconsistent(int, Coord);
};

#endif