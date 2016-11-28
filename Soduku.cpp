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
    init_grid(filename);
    if (solve()) {
        std::cout << "solved " << filename << "!\n";
    } else {
        std::cout << filename << " not solved ... uh oh\n";
        printDomains(domains);
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
            std::cout << c << " = " << domains[c] << "\n";
        }
        std::cout << std::endl;
    }
}
bool Soduku::solve()
{
    if (not prune_grid(domains)) {
        return false;
    }
    HashMap<Coord, Set<int>> copy_domains(this->domains);
    return search(copy_domains);
}
bool Soduku::prune_grid(HashMap<Coord, Set<int>> &domains)
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
    if (solved(domains)) {
        this->domains = domains;
        return true;
    } 
    Coord c = select_unassigned_variable(domains);

    Set<int> c_domains(domains[c]);
    while (not c_domains.empty()) {
        int d = c_domains.pop();
        HashMap<Coord, Set<int>> copy_domains(domains);
        if (assign(copy_domains, c, d) and search(copy_domains)) {
            domains = copy_domains;
            return true;
        }        
    }
    return false;

}
bool Soduku::solved(HashMap<Coord, Set<int>> &domains) 
{
    for (HashMap<Coord, Set<int>>::key_iterator key = domains.begin(); 
         key != domains.end(); ++key) {
        size_t size = domains[*key].size();
        if (size != 1) {
            return false;
        }
        assert(size > 0);
    }
    return true;
}
Coord Soduku::select_unassigned_variable(HashMap<Coord, Set<int>> &domains)
{
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
    assert(c[0] != gridSize);
    return c;
}

bool Soduku::assign(HashMap<Coord, Set<int>> &domains, Coord c, int d)
{
    Set<int> *other_domains = new Set<int>(domains[c]);
    while (not other_domains->empty()) {
        int d2 = other_domains->pop();
        if (d2 != d and not eliminate(domains, c, d2)) {
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
    if ((not (eliminate_from_peers(domains, c))) or 
         not (check_unique_remaining_values(domains, c, d))) {
        return false;
    }
    return true;
}
bool Soduku::eliminate_from_peers(HashMap<Coord, Set<int>> &domains, Coord c)
{
    if (domains[c].empty()) {
        return false; // sanity check
    } 
    else if (domains[c].size() == 1) {
        int d = domains[c].top();
        for (Set<Coord>::iterator it = peers[c].begin(); it != peers[c].end(); ++it) {
            Coord c2 = *it;
            if (not eliminate(domains, c2, d)) {
                return false;
            }
        }
    }
    return true;
}
bool Soduku::check_unique_remaining_values(HashMap<Coord, Set<int>> &domains, Coord c, int d)
{
    for (int i = 0; i < (int) units[c].size(); i++) {
        std::vector<Coord> dplaces;
        for (int j = 0; j < (int) units[c][i].size(); j++) {
            Coord c2 = units[c][i][j];
            if (domains[c2].contains(d)) {
                dplaces.push_back(c2);
            } 
        }
        if ((dplaces.size() == 0) or 
            (dplaces.size() == 1 and not assign(domains, dplaces[0], d))) {
            return false;
            }
    }
    return true;
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
            puzzle.insert(c, num);
            domains.insert(c, Set<int>());
            for (int i = 1; i < gridSize + 1; i++) {
                domains[c].add(i);
            }
        }
    } 
}
void Soduku::init_data_structures()
{
    for (int j = 0; j < gridSize; j++) {
        allunits.push_back(std::vector<Coord>());
        allunits.push_back(std::vector<Coord>());
        for (int i = 0; i < gridSize; i++) {
            Coord c1(i, j); Coord c2(j, i);
            allunits[2 * j].push_back(c1);
            allunits[2 * j + 1].push_back(c2);
            units.insert(c1, std::vector<std::vector<Coord>>());
            peers.insert(c1, Set<Coord>()); }}

    for (int i = 0; i < gridSize; i += n) {
        for (int j = 0; j < gridSize; j += n) {
            allunits.push_back(std::vector<Coord>());
            int size = allunits.size();
            for (int k = i; k < n + i; k++) {
                for (int l = j; l < n + j; l++) {
                    Coord c(l, k);
                    allunits[size - 1].push_back(c); }}}} 

    for (int i = 0; i < (int) allunits.size(); i++) {
        for (int j = 0; j < (int) allunits[i].size(); j++) {
            Coord c = allunits[i][j];
            units[c].push_back(std::vector<Coord>(allunits[i]));
            for (int k = 0; k < (int) allunits[i].size(); k++) {
                if (k != j) {
                    Coord c2 = allunits[i][k];
                    peers[c].add(c2); }}}}
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