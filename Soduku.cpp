#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <stack>
#include <math.h>
#include <cassert>
#include "Soduku.h"
#include "Set/Set.h"
#include "Coord/Coord.h"
#include "HashMap/HashMap.h"


Soduku::Soduku(std::string filename, int size)
{
    gridSize = size;
    n = (int) sqrt(size);
    init(filename);
    if (solve()) {
        std::cout << "solved!\n";
    } else {
        std::cout << "not solved ...uh oh\n";
    }
    print();
}
Soduku::~Soduku()
{

}
void Soduku::print()
{
    for (int j = 0; j < gridSize; j++) {
        for (int i = 0; i < gridSize; i++) {
            Coord c(i, j);
            if (values[c].size() == 1) {
                 std::cout << "\033[1m\033[31m" << values[c].top() << "\033[0m ";
            } else {
                std::cout << "\033[37m0 \033[0m";
            }
        }
        std::cout << std::endl;
    }
}

bool Soduku::solve()
{
    for(std::map<Coord, int>::iterator i = puzzle.begin();
        i != puzzle.end(); i++) {
        Coord c = i->first;
        int   d = i->second;
        //std::cout << "solve(): at " << c << " d = " << d << std::endl;
        if (d != 0 and not assign(c, d)) {
            std::cout << "solve(): returning false because assignment " << c << " = " << d << " failed\n";
            return false;
        }
    }
    return true;
}
bool Soduku::assign(Coord c, int d)
{
    Set<int> *other_values = new Set<int>(values[c]);
    while (not other_values->empty()) {
        int d2 = other_values->pop();
        if (d2 != d and not eliminate(c, d2)) {
            std::cout << "assign(): returning false because eliminating " << d2 << " from " << c << " failed\n";
            return false;
        }
    }
    delete other_values;
    return true;
}
bool Soduku::eliminate(Coord c, int d)
{
    if (not values[c].contains(d)) {
        return true;
    }
    values[c].remove(d);
    if (values[c].empty()) {
        std::cout << "eliminate(): retruning false because values[c].empty() for c = "<< c << "\n";
        return false; // sanity check
    } else if (values[c].size() == 1) {
        int d2 = values[c].top();
        for (Set<Coord>::iterator it = peers[c].begin(); it != peers[c].end(); ++it) {
            Coord c2 = *it;
            if (not eliminate(c2, d2)) {
                return false;
            }
        }
    }
    for (int i = 0; i < (int) units[c].size(); i++) {
        std::vector<Coord> dplaces;
        for (int j = 0; j < (int) units[c][i].size(); j++) {
            Coord c3 = units[c][i][j];
            if (values[c3].contains(d)) {
                dplaces.push_back(c3);
            } 
        }
        if (dplaces.size() == 0) {
            std::cout << "eliminate(): returning false because dplaces.size() == 0 \n";
            
            return false;
        } else if (dplaces.size() == 1) {
            if (not assign(dplaces[0], d)) {
                std::cout << "eliminate(): returning false because assignment " << dplaces[0] << " = " << d << " failed\n";
            
                return false;
            }
        }
    }
    return true;


}
void Soduku::init(std::string filename)
{
    init_data_structures();
    init_grid(filename);

}
void Soduku::init_grid(std::string filename)
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
            Coord c(i, j);
            inFile >> s;
            int num = string2int(s);
            puzzle[c] = num;
            values.insert(c, Set<int>());
            for (int i = 1; i < gridSize + 1; i++) {
                values[c].add(i);
            }
            values[c].print();
        }
    }
    assert(puzzle.size() == 81);
    //assert(values.size() == 81);
    for (HashMap<Coord, Set<int>>::iterator i = values.begin();
         i != values.end(); ++i) {
        std::cout << i.key() << ": ";
        i.value().print();
        std::cout << std::endl;
        assert(i.value().size() == 9);
    }
        


}
void Soduku::init_data_structures()
{
    for (int j = 0; j < gridSize; j++) {
        allunits.push_back(std::vector<Coord>());
        allunits.push_back(std::vector<Coord>());
        for (int i = 0; i < gridSize; i++) {
            Coord c1(i, j);
            Coord c2(j, i);
            allunits[2 * j].push_back(c1);
            allunits[2 * j + 1].push_back(c2);
            units.insert(c1, std::vector<std::vector<Coord>>());
            peers.insert(c1, Set<Coord>());
        }
    }
    for (int i = 0; i < gridSize; i += n) {
        for (int j = 0; j < gridSize; j += n) {
            allunits.push_back(std::vector<Coord>());
            int size = allunits.size();
            for (int k = i; k < n + i; k++) {
                for (int l = j; l < n + j; l++) {
                    Coord c(l, k);
                    allunits[size - 1].push_back(c);
                }
            }
        }
    }
    for (int i = 0; i < (int) allunits.size(); i++) {
        for (int j = 0; j < (int) allunits[i].size(); j++) {
            Coord c = allunits[i][j];
            units[c].push_back(std::vector<Coord>(allunits[i]));
            for (int k = 0; k < (int) allunits[i].size(); k++) {
                if (k != j) {
                    Coord c2 = allunits[i][k];
                    peers[c].add(c2);
                }
            }
        }
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