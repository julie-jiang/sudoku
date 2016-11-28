#include <iostream>
#include <sstream>
#include <fstream>
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
    init_data_structures();
    HashMap<Coord, Set<int>> values;
    init_grid(values, filename);
    if (solve(values)) {
        std::cout << "solved!\n";
    } else {
        std::cout << "not solved ... uh oh\n";
    }
    print(values);
}
Soduku::~Soduku()
{

}
void Soduku::print(HashMap<Coord, Set<int>> &values)
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
void Soduku::printValues(HashMap<Coord, Set<int>> &values)
{
    for (int j = 0; j < gridSize; j++) {
        for (int i = 0; i < gridSize; i++) {
            Coord c(i, j);
            std::cout << c << " = ";
            values[c].print();
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
}
bool Soduku::solve(HashMap<Coord, Set<int>> &values)
{
    if (not parse_grid(values)) {
        return false;
    }
    return search(values);
}
bool Soduku::parse_grid(HashMap<Coord, Set<int>> &values)
{
    for(HashMap<Coord, int>::key_iterator key = puzzle.begin();
        key != puzzle.end(); ++key) {
        Coord c = *key;
        int   d = puzzle[c];
        //std::cout << "solve(): at " << c << " d = " << d << std::endl;
        if (d != 0 and not assign(values, c, d)) {
            std::cout << "solve(): returning false because assignment " << c << " = " << d << " failed\n";
            return false;
        }
    }
    return true;
}

bool Soduku::search(HashMap<Coord, Set<int>> &values)
{
    std::cout << "......searching......\n";
    bool solved = true;
    for (HashMap<Coord, Set<int>>::key_iterator key = values.begin(); 
         key != values.end(); ++key) {
        size_t size = values[*key].size();
        if (size != 1) {
            solved = false;
            break;
        } else if (size < 1) {
            std::cout << "values[*key].size() == 0! returning false. key = " << *key << " values = ";
            values[*key].print();
            std::cout << "\n";
            return false;
        }
    }
    if (solved) {
        print(values);
        return true;
    } 
    Coord c(gridSize, gridSize);
    size_t min_possibilities = gridSize + 1;
    for (HashMap<Coord, Set<int>>::key_iterator it = values.begin();
         it != values.end(); ++it) {
        size_t size = values[*it].size();
        if (size > 1 and size < min_possibilities) {
            min_possibilities = size;
            c = *it;
        }
    }

    Coord dummy(gridSize, gridSize);
    if (c == dummy) {
        std::cout << "c == dummy! exiting\n";
        printValues(values);
        return false;
    }
    std::cout << "min possibilities c = " << c << ". ";
    std::cout << "values[c] = ";
    values[c].print();
    std::cout << "\n";
    print(values);
    HashMap<Coord, Set<int>> copy_values(values);
    Set<int> c_values(copy_values[c]);
    while (not c_values.empty()) {
        int d = c_values.pop();
        std::cout << "values should not have changed: ";
        copy_values[c].print();
        std::cout << "\n";
        std::cout << "search(): assigning " << c << " to " << d << "\n";
        HashMap<Coord, Set<int>> copy_copy_values(copy_values);
        if (assign(copy_copy_values, c, d)) {
            copy_values = copy_copy_values;
            return search(copy_values);
        } else {
            std::cout << "search(): assignment " << c << " to " << d << " unsuccessful.\n";
        }
    }     
    return false;

}

bool Soduku::assign(HashMap<Coord, Set<int>> &values, Coord c, int d)
{
    Set<int> *other_values = new Set<int>(values[c]);
    while (not other_values->empty()) {
        int d2 = other_values->pop();
        if (d2 != d and not eliminate(values, c, d2)) {
            std::cout << "      assign(): returning false because eliminating " << d2 << " from " << c << " failed\n";
            return false;
        }
    }
    delete other_values;
    return true;
}
bool Soduku::eliminate(HashMap<Coord, Set<int>> &values, Coord c, int d)
{
    if (not values[c].contains(d)) {
        return true;
    }
    values[c].remove(d);
    if (values[c].empty()) {
        std::cout << "              eliminate(): retruning false because values[c].empty() for c = "<< c << "\n";
        return false; // sanity check
    } else if (values[c].size() == 1) {
        int d2 = values[c].top();
        for (Set<Coord>::iterator it = peers[c].begin(); it != peers[c].end(); ++it) {
            Coord c2 = *it;
            if (not eliminate(values, c2, d2)) {
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
            std::cout << "              eliminate(): returning false because dplaces.size() == 0 for a unit of " << c << " for d = " << d << "\n";
            /*std::cout << "====";
            for (int j = 0; j < (int) units[c][i].size(); j++) {
                std::cout << units[c][i][j] << " ";
            }
            
            std::cout << "\n";*/
            
            return false;
        } else if (dplaces.size() == 1) {
            if (not assign(values, dplaces[0], d)) {
                std::cout << "              eliminate(): returning false because assignment " << dplaces[0] << " = " << d << " failed\n";
                return false;
            }
        }
    }
    return true;


}

void Soduku::init_grid(HashMap<Coord, Set<int>> &values, std::string filename)
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
            puzzle.insert(c, num);
            values.insert(c, Set<int>());
            for (int i = 1; i < gridSize + 1; i++) {
                values[c].add(i);
            }
        }
    } 
    for (HashMap<Coord, Set<int>>::key_iterator key = values.begin();
         key != values.end(); ++key) {
        assert(values[*key].size() == 9);
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
    /*
    for (HashMap<Coord, std::vector<std::vector<Coord>>>::key_iterator it = units.begin();
        it != units.end(); ++it) {
        std::cout << "======== units for cooord " << *it << std::endl;
        Coord c(*it);
        for (int i = 0; i < (int) units[c].size(); i++) {
            for (int j = 0; j < (int) units[c][i].size(); j++) {
                std::cout << units[c][i][j] << " ";
            }
            std::cout << std::endl;
        }
    }*/
 
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