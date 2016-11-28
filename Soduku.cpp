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
    HashMap<Coord, Set<int>> domains;
    init_grid(domains, filename);
    if (solve(domains)) {
        std::cout << "solved!\n";
    } else {
        std::cout << "not solved ... uh oh\n";
    }
    print(domains);
}
Soduku::~Soduku()
{

}
void Soduku::print(HashMap<Coord, Set<int>> &domains)
{
    for (int j = 0; j < gridSize; j++) {
        for (int i = 0; i < gridSize; i++) {
            Coord c(i, j);
            if (domains[c].size() == 1) {
                 std::cout << "\033[1m\033[31m" << domains[c].top() << "\033[0m ";
            } else {
                std::cout << "\033[37m0 \033[0m";
            }
        }
        std::cout << std::endl;
    }
}
void Soduku::printDomains(HashMap<Coord, Set<int>> &domains)
{
    for (int j = 0; j < gridSize; j++) {
        for (int i = 0; i < gridSize; i++) {
            Coord c(i, j);
            std::cout << c << " = ";
            domains[c].print();
            std::cout << "\n";
        }
        std::cout << std::endl;
    }
}
bool Soduku::solve(HashMap<Coord, Set<int>> &domains)
{
    if (not parse_grid(domains)) {
        return false;
    }
    return search(domains);
}
bool Soduku::parse_grid(HashMap<Coord, Set<int>> &domains)
{
    for(HashMap<Coord, int>::key_iterator key = puzzle.begin();
        key != puzzle.end(); ++key) {
        Coord c = *key;
        int   d = puzzle[c];
        if (d != 0 and not assign(domains, c, d)) {
            return false;
        }
    }
    return true;
}

bool Soduku::search(HashMap<Coord, Set<int>> &domains)
{
    bool solved = true;
    for (HashMap<Coord, Set<int>>::key_iterator key = domains.begin(); 
         key != domains.end(); ++key) {
        size_t size = domains[*key].size();
        if (size != 1) {
            solved = false;
            break;
        }
        assert(size != 0);
    }
    if (solved) {
        print(domains);
        return true;
    } 
    Coord c(gridSize, gridSize);
    size_t min_possibilities = gridSize + 1;
    for (HashMap<Coord, Set<int>>::key_iterator it = domains.begin();
         it != domains.end(); ++it) {
        size_t size = domains[*it].size();
        if (size > 1 and size < min_possibilities) {
            min_possibilities = size;
            c = *it;
        }
    }

    Coord dummy(gridSize, gridSize);
    assert(c != dummy);

    HashMap<Coord, Set<int>> copy_domains(domains);
    Set<int> c_domains(copy_domains[c]);
    while (not c_domains.empty()) {
        int d = c_domains.pop();
        HashMap<Coord, Set<int>> copy_copy_domains(copy_domains);
        if (assign(copy_copy_domains, c, d)) {
            copy_domains = copy_copy_domains;
            return search(copy_domains);
        }
    }     
    return false;

}

bool Soduku::assign(HashMap<Coord, Set<int>> &domains, Coord c, int d)
{
    Set<int> *other_domains = new Set<int>(domains[c]);
    while (not other_domains->empty()) {
        int d2 = other_domains->pop();
        if (d2 != d and not eliminate(domains, c, d2)) {
            std::cout << "      assign(): returning false because eliminating " << d2 << " from " << c << " failed\n";
            return false;
        }
    }
    delete other_domains;
    return true;
}
bool Soduku::eliminate(HashMap<Coord, Set<int>> &domains, Coord c, int d)
{
    if (not domains[c].contains(d)) {
        return true;
    }
    domains[c].remove(d);
    if (domains[c].empty()) {
        std::cout << "              eliminate(): retruning false because domains[c].empty() for c = "<< c << "\n";
        return false; // sanity check
    } else if (domains[c].size() == 1) {
        int d2 = domains[c].top();
        for (Set<Coord>::iterator it = peers[c].begin(); it != peers[c].end(); ++it) {
            Coord c2 = *it;
            if (not eliminate(domains, c2, d2)) {
                return false;
            }
        }
    }
    for (int i = 0; i < (int) units[c].size(); i++) {
        std::vector<Coord> dplaces;
        for (int j = 0; j < (int) units[c][i].size(); j++) {
            Coord c3 = units[c][i][j];
            if (domains[c3].contains(d)) {
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
            if (not assign(domains, dplaces[0], d)) {
                std::cout << "              eliminate(): returning false because assignment " << dplaces[0] << " = " << d << " failed\n";
                return false;
            }
        }
    }
    return true;


}

void Soduku::init_grid(HashMap<Coord, Set<int>> &domains, std::string filename)
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
            domains.insert(c, Set<int>());
            for (int i = 1; i < gridSize + 1; i++) {
                domains[c].add(i);
            }
        }
    } 
    for (HashMap<Coord, Set<int>>::key_iterator key = domains.begin();
         key != domains.end(); ++key) {
        assert(domains[*key].size() == 9);
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