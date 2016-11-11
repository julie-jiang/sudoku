#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <algorithm>
#include "Soduku.h"
#include "AVLTree.h"

Soduku::Soduku(std::string filename, int size)
{
	gridSize = size;
    
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
            grid.insert(std::pair<Coord, std::vector<int>>(c, 
                        AVLTree<int>());
            inFile >> s;
            int ints = string2int(s);
            if (ints != 0) 
                grid[c].push_back(ints);
            else {
                grid[c].push_back(1);
                grid[c].push_back(2);
                grid[c].push_back(3);
                grid[c].push_back(4);
                grid[c].push_back(5);
                grid[c].push_back(6);
                grid[c].push_back(7);
                grid[c].push_back(8);
                grid[c].push_back(9);
                Queue.push(c);
            }
        }
    }
    printGrid();
    std::cout << "---------------------------\n";
    arcConsistency();
    printGrid();

}

Soduku::~Soduku()
{

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

void Soduku::printGrid()
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

void Soduku::arcConsistency()
{
    while (not Queue.empty()) {
        Coord c = Queue.front();
        Queue.pop();
        validateDomain(c);
    }
}
bool Soduku::validateDomain(Coord c)
{
    bool removed = false;
    for (int i = 0; i < (int) grid[c].size(); i++) {
        if (valueIsInconsistent(domain[i], c)) {
            removed = true;
            ;
        }
    }
    return removed;
}
bool Soduku::valueIsInconsistent(int item, Coord c)
{
    int x, y;
    std::tie(x, y) = c;
    for (int i = 0; i < gridSize; i++) {
        if (i != y and grid[std::make_pair(x, i)].contains(item))
            return false;
        if (i != x and gric[std::make_pair(i, y)].contains(item))
            return false;
    }
    return true;
}