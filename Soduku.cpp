#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <stack>
#include <math.h>
#include "Soduku.h"
#include "AVLTree.h"

Soduku::Soduku(std::string filename, int size)
{
	gridSize = size;
    n = (int) sqrt(size);
    std::map<Coord, int> assignment;
    initGrid(filename, assignment);
    //bool result = backtrackingSearch(assignment);
}
Soduku::~Soduku()
{

}


void Soduku::initGrid(std::string filename, std::map<Coord, int> &assignment)
{
    // Open file 
	std::ifstream inFile;
    inFile.open(filename);
    if (inFile.fail()) {
        throw std::logic_error("File does not exist");
    }

    // Read input and initialize grid
    std::string s;
    for (int j = 0; j < gridSize; j++) {
        for (int i = 0; i < gridSize; i++) {
            Coord c = std::make_pair(i, j);
            grid.insert(std::pair<Coord, AVLTree<int>>(c, AVLTree<int>()));
            inFile >> s;
            int num = string2int(s);
            if (num != 0) {
                grid[c].add(num);
                assignment[c] = num;
            } else {
                for (int i = 1; i < 10; i++) {
                    grid[c].add(i);
                } 
                Queue.push(c);
                PQueue.push(c);

            }
        }
    }
    enforceArcConsistency(assignment);
    printGridDomains();
}

bool Soduku::backtrackingSearch(std::map<Coord, int> &assignment)
{   
    if (not PQueue.empty()) {
        Coord c = selectUnassignedVaraible();
        std::stack<int> domain(grid[c].getElements());
        while (not domain.empty()) {
            int d = domain.top();
            domain.pop();
            if (valueIsConsistent(d, c, assignment)) {
                assignment[c] = d;
                int x, y;
                std::tie(x, y) = c;
                print(assignment);
                std::cout << "Assigned (" << x << ", " << y << ") to " << d << std::endl;
                if (backtrackingSearch(assignment))
                    return true;
                assignment.erase(c);
            }
        }
    }
    return false;
    
}
Soduku::Coord Soduku::selectUnassignedVaraible()
{
    Coord c = PQueue.front();
    PQueue.pop();
    return c;
}
void Soduku::addToQueue(Coord c)
{
    int x, y;
    std::tie(x, y) = c;
    for (int i = 0; i < gridSize; i++) {
        if (i != y and grid[std::make_pair(x, i)].size() > 1) 
            Queue.push(std::make_pair(x, i));
        
        if (i != x and grid[std::make_pair(i, y)].size() > 1) 
            Queue.push(std::make_pair(i, y));
    }
    // Check subgrid
    for (int i = x - x % n; i < n + x - x % n; i++) {
        for (int j = y - y % n; j < n + y - y % n; j++) {
            if (i != x and j != y and grid[std::make_pair(i, j)].size() > 1)
                Queue.push(std::make_pair(i, j));
        }
    }
}
void Soduku::enforceArcConsistency(std::map<Coord, int> &assignment)
{
    while (not Queue.empty()) {
        Coord c = Queue.front();
        Queue.pop();
        int x,y;
        std::tie(x,y) = c;
        removeInconsistentValues(c, assignment);
    }
    for (std::map<Coord, AVLTree<int>>::iterator i = grid.begin(); i != grid.end(); i++){
        if (i->second.size() == 1) {
            assignment[i->first] = i->second.getRoot();
        } if (i->second.empty()) {
            throw std::logic_error("");
        }
    }
}
bool Soduku::removeInconsistentValues(Coord c, std::map<Coord, int> &assignment)
{
    bool removed = false;
    std::stack<int> domain = grid[c].getElements();
    while (not domain.empty()) {
        int d = domain.top();
        domain.pop();
        if (not valueIsConsistent(d, c, assignment)) {
            removed = true;
            grid[c].remove(d);
        }
    }
    return removed;
}
bool Soduku::valueIsConsistent(int d, Coord c, std::map<Coord, int> &assignment)
{
    int x, y;
    std::tie(x, y) = c;
    // Check row and column
    for (int i = 0; i < gridSize; i++) {
        if ((i != y and assignment[std::make_pair(x, i)] == d) or 
            (i != x and assignment[std::make_pair(i, y)] == d)) 
            return false;
    }
    // Check subgrid
    for (int i = x - x % n; i < n + x - x % n; i++) {
        for (int j = y - y % n; j < n + y - y % n; j++) {
            if (i != x and j != y and assignment[std::make_pair(i, j)] == d)
                return false;
        }
    }
    return true;
}

void Soduku::print(std::map<Coord, int> &assignment)
{
    std::cout << ("\033[H\033[2J");
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (assignment.find(std::make_pair(i, j)) != assignment.end())
                std::cout << assignment[std::make_pair(i, j)] << " ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

void Soduku::printGridDomains()
{
    for (std::map<Coord, AVLTree<int>>::iterator i = grid.begin();
        i != grid.end(); i++) {
        int x, y;
        std::tie(x, y) = i->first;
        std::cout << x << " " << y << " =>";
        i->second.print();
        std::cout << std::endl;
    }
}



int Soduku::string2int(std::string s)
{
    std::stringstream ss(s);
    int result;

    ss >> result;
    if (ss.fail())
        throw std::runtime_error("string2int: non-numeric value: " + s);

    return result;
}






