#ifndef SODUKU_H
#define SODUKU_H
#include <cstdlib>
#include <queue>
#include <map>
#include "AVLTree/AVLTree.h"
#include "Coord/Coord.h"

class Soduku {

public:
    Soduku(std::string, int);
    ~Soduku();

private:
    int gridSize, n;
    //typedef std::pair<int, int> Coord;
    std::map<Coord, AVLTree<int>> grid;
    std::map<Coord, int> permAssignment;
    std::map<Coord, int> assignment;

    std::queue<Coord> PQueue;
    std::queue<Coord> Queue;

    void initGrid(std::string);
    bool backtrackingSearch();
    void addToDomain(std::map<Coord, AVLTree<int>> *);
    std::map<Coord, AVLTree<int>> *forwardCheck(Coord, int);
    Coord selectUnassignedVariable();
    void addToQueue(Coord);
    void print();
    void printGridDomains();
    void printAssignments();
    void printAssignmentGridDomains();
    void enforceArcConsistency();
    bool removeInconsistentValues(Coord);
    bool valueIsConsistent(int, Coord);
    int string2int(std::string);
    std::string int2string(int);

};

#endif