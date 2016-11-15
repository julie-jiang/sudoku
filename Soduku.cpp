#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <stack>
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
            grid.insert(std::pair<Coord, AVLTree<int>>(c, 
                        AVLTree<int>()));
            inFile >> s;
            int ints = string2int(s);
            if (ints != 0) 
                grid[c].add(ints);
            else {
                grid[c].add(1);
                grid[c].add(2);
                grid[c].add(3);
                grid[c].add(4);
                grid[c].add(5);
                grid[c].add(6);
                grid[c].add(7);
                grid[c].add(8);
                grid[c].add(9);
                Queue.push(c);
            }
        }
    }
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
        int x, y;
        std::tie(x, y) = c;
        std::cout << "checking coordinates " << x << " " << y << "..."; 
        Queue.pop();
        validateDomain(c);
        std::cout << std::endl;
    }
}
bool Soduku::validateDomain(Coord c)
{
    bool removed = false;
    std::stack<int> domain = grid[c].getElements();
    while (not domain.empty()) {
        int item = domain.top();
        std::cout << item << " ";
        domain.pop();
        if (valueIsInconsistent(item, c)) {
            removed = true;
            int x, y;
            std::tie(x, y) = c;
            std::cout << "removing x = " << item << " from the domain of coordinates " << x << " " << y << std::endl;
            grid[c].remove(item);
        }
    }
    return removed;
}
bool Soduku::valueIsInconsistent(int item, Coord c)
{
    int x, y;
    std::tie(x, y) = c;
    for (int i = 0; i < gridSize; i++) {
        if ((i != y and grid[std::make_pair(x, i)].contains(item)) or 
            (i != x and grid[std::make_pair(i, y)].contains(item)))
            return true;
    }
    return false;
}