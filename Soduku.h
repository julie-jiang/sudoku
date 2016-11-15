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
	int gridSize, n;
	typedef std::pair<int, int> Coord;
	std::map<Coord, AVLTree<int>> grid;

	std::queue<Coord> PQueue;
	std::queue<Coord> Queue;

	void initGrid(std::string, std::map<Coord, int> &);
	bool backtrackingSearch(std::map<Coord, int> &);
	Coord selectUnassignedVaraible();
	void addToQueue(Coord);
	void print(std::map<Coord, int> &);
	void printGridDomains();
	void enforceArcConsistency(std::map<Coord, int> &);
	bool removeInconsistentValues(Coord, std::map<Coord, int> &);
	bool valueIsConsistent(int, Coord, std::map<Coord, int> &);
	int string2int(std::string);
};

#endif