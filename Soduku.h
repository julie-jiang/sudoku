#ifndef SODUKU_H
#define SODUKU_H
#include <cstdlib>
#include <queue>
#include <map>
#include "AVLTree.h"
#include "Coord.h"

class Soduku {

public:
	Soduku(std::string, int);
	~Soduku();

private:
	int gridSize, n;
	std::map<Coord, AVLTree<int>> grid;
	std::map<Coord, int> givenAssignment;
	std::map<Coord, int> assignment;

	std::queue<Coord> PQueue;
	std::queue<Coord> Queue;

	void initGrid(std::string);
	bool backtrackingSearch();
	Coord selectUnassignedVaraible();
	void addToQueue(Coord);
	void print();
	void printGridDomains();
	void enforceArcConsistency();
	bool removeInconsistentValues(Coord);
	bool valueIsConsistent(int, Coord);
	int string2int(std::string);
	std::string int2string(int);

};

#endif