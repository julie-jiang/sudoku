#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <stack>
#include <math.h>
#include "Soduku.h"
#include "Set/Set.h"
#include "Coord/Coord.h"

Soduku::Soduku(std::string filename, int size)
{
    gridSize = size;
    n = (int) sqrt(size);
    initGrid(filename);
    bool result = backtrackingSearch();
}
Soduku::~Soduku()
{

}


void Soduku::initGrid(std::string filename)
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
            grid.insert(std::pair<Coord, Set<int>>(c, Set<int>()));
            inFile >> s;
            int num = string2int(s);
            if (num != 0) {
                grid[c].add(num);
                permAssignment[c] = num;
            } else {
                for (int i = 1; i < 10; i++) {
                    grid[c].add(i);
                } 
                Queue.push(c);
                
            }
        }
    }
    enforceArcConsistency();
    for (std::map<Coord, Set<int>>::iterator i = grid.begin(); i != grid.end(); i++){
        if (i->second.empty()) {
            throw std::logic_error("");
        } 
        if (i->second.size() == 1) {
            assignment[i->first] = i->second.top(); 
        } else {
            PQueue.push(i->first);
        }
    }
    printGridDomains();
}
bool Soduku::backtrackingSearch()
{   
    if (not PQueue.empty()) {
        Coord c = selectUnassignedVariable();
        while (not grid[c].empty()) {
            int d = grid[c].pop();
            if (valueIsConsistent(d, c)) {
                assignment[c] = d;
                std::map<Coord, Set<int>> *eliminatedDomains = forwardCheck(c, d);

                std::cout << ("\033[H\033[2J");
                std::cout << "Assigned " << c << " to " << d << std::endl;
                print();
                // print eliminated domains
                std::cout << "Eliminated: \n";
                for (std::map<Coord, Set<int>>::iterator i = eliminatedDomains->begin();
                     i != eliminatedDomains->end(); i++) {
                    std::cout << i->first << " => ";
                    i->second.print();
                    std::cout << std::endl;
                }
                //printAssignmentGridDomains();
                char a; // Wait for user input before continuing
                std::cin >> a;
                if (backtrackingSearch()) {
                    std::cout << c << " = " << d << " worked!!!\n";
                    return true;
                } 
                std::cout << c << " = " << d << " didn't workout, backtracking\n";
                eraseAssignment(c, d);
                addToDomain(eliminatedDomains);
            } else {
                std::cout << ("\033[H\033[2J");
                std::cout << c << " = " << d << " is not consistent! Next!\n";
            }
        }
        PQueue.push(c);
    }
    return false;
}
void Soduku::eraseAssignment(Coord c, int d)
{
    assignment.erase(c);
    int x = c[0];
    int y = c[1];

}
void Soduku::addToDomain(std::map<Coord, Set<int>> *eliminatedDomains)
{
    for (std::map<Coord, Set<int>>::iterator i = eliminatedDomains->begin();
         i != eliminatedDomains->end(); i++) {
        while (not i->second.empty()) {
            int d = i->second.pop();
            grid[i->first].add(d);
        }
    }
}
std::map<Coord, Set<int>> *Soduku::forwardCheck(Coord c, int d)
{
    std::map<Coord, Set<int>> *eliminatedDomains = new std::map<Coord, Set<int>>;
    
    int x = c[0];
    int y = c[1];
    for (int i = 0; i < gridSize; i++) {
        Coord c1(x, i);
        Coord c2(i, y);
        if (i != y and grid[c1].contains(d)) {
            std::cout << c1 << " contains " << d << ", removing it\n";
            grid[c1].remove(d);
            if (eliminatedDomains->find(c1) == eliminatedDomains->end())
                eliminatedDomains->insert(std::pair<Coord, Set<int>>(c1, Set<int>()));
            (*eliminatedDomains)[c1].add(d);
            if (grid[c1].size == 1) {
                std::cout << "Assigned " << c1 << " to " << grid[c1].top() << std::endl;
                assignment[c1] = grid[c1].top();
            }
        } 
        if (i != x and grid[c2].contains(d)) {
            std::cout << c2 << " contains " << d << ", removing it\n";
            grid[c2].remove(d);
            if (eliminatedDomains->find(c2) == eliminatedDomains->end())
                eliminatedDomains->insert(std::pair<Coord, Set<int>>(c2, Set<int>()));
            (*eliminatedDomains)[c2].add(d);
            if (grid[c2].size == 1) {
                std::cout << "Assigned " << c2 << " to " << grid[c2].top() << std::endl;
                assignment[c2] = grid[c2].top();
            }
        }
    }
    for (int i = x - x % n; i < n + x - x % n; i++) {
        for (int j = y - y % n; j < n + y - y % n; j++) {
            Coord c3(i, j);
            if (i != x and j != y and grid[c3].contains(d)) {
                std::cout << c3 << " contains " << d << ", removing it\n";
                grid[c3].remove(d);
                if (eliminatedDomains->find(c3) == eliminatedDomains->end())
                    eliminatedDomains->insert(std::pair<Coord, Set<int>>(c3, Set<int>()));
                (*eliminatedDomains)[c3].add(d);
                if (grid[c3].size == 1) {
                    std::cout << "Assigned " << c3 << " to " << grid[c3].top() << std::endl;
                    assignment[c3] = grid[c3].top();
            }
            }
        }
    }
    return eliminatedDomains;


}
bool Soduku::valueIsConsistent(int d, Coord c)
{
    int x = c[0];
    int y = c[1];
    // Check row and column
    for (int i = 0; i < gridSize; i++) {
        Coord c1(x, i);
        Coord c2(i, y);
        if ((i != y and permAssignment.find(c1) != permAssignment.end() 
             and permAssignment[c1] == d) or 
            (i != x and permAssignment.find(c2) != permAssignment.end()
             and permAssignment[c2] == d)) 
            return false;
    }
    // Check subgrid
    for (int i = x - x % n; i < n + x - x % n; i++) {
        for (int j = y - y % n; j < n + y - y % n; j++) {
            Coord c3(i, j);
            if (i != x and j != y 
                and permAssignment.find(c3) != permAssignment.end() 
                and permAssignment[c3] == d)
                return false;
        }
    }
    // Check row and column
    for (int i = 0; i < gridSize; i++) {
        Coord c1(x, i);
        Coord c2(i, y);
        if ((i != y and assignment.find(c1) != assignment.end() 
             and assignment[c1] == d) or 
            (i != x and assignment.find(c2) != assignment.end()
             and assignment[c2] == d)) 
            return false;
    }
    // Check subgrid
    for (int i = x - x % n; i < n + x - x % n; i++) {
        for (int j = y - y % n; j < n + y - y % n; j++) {
            Coord c3(i, j);
            if (i != x and j != y 
                and assignment.find(c3) != assignment.end() 
                and assignment[c3] == d)
                return false;
        }
    }
    return true;
}
void Soduku::printAssignments()
{
    std::cout << "Current assignments: \n";
    for (std::map<Coord, int>::iterator i = assignment.begin();
        i != assignment.end(); i++) {
        std::cout << i->first << " = " << i->second << std::endl;
    }
}
Coord Soduku::selectUnassignedVariable()
{
    Coord c = PQueue.front();
    PQueue.pop();
    return c;
}
void Soduku::addToQueue(Coord c)
{
    int x = c[0];
    int y = c[1];
    for (int i = 0; i < gridSize; i++) {
        Coord c1(x, i); 
        Coord c2(i, y);
        if (i != y and grid[c1].size() > 1) 
            Queue.push(c1);
        
        if (i != x and grid[c2].size() > 1) 
            Queue.push(c2);
    }
    // Check subgrid
    for (int i = x - x % n; i < n + x - x % n; i++) {
        for (int j = y - y % n; j < n + y - y % n; j++) {
            Coord c3(i, j);
            if (i != x and j != y and grid[c3].size() > 1)
                Queue.push(c3);
        }
    }
}
void Soduku::enforceArcConsistency()
{
    while (not Queue.empty()) {
        Coord c = Queue.front();
        Queue.pop();
        removeInconsistentValues(c);

    }

}
bool Soduku::removeInconsistentValues(Coord c)
{
    bool removed = false;
    std::stack<int> domain = grid[c].getElements();
    while (not domain.empty()) {
        int d = domain.top();
        domain.pop();
        if (not valueIsConsistent(d, c)) {
            removed = true;
            grid[c].remove(d);
        }
    }
    return removed;
}


void Soduku::print()
{
    for (int j = 0; j < gridSize; j++) {
        for (int i = 0; i < gridSize; i++) {
            Coord c(i, j);
            std::map<Coord, int>::iterator it = permAssignment.find(c);
            if (it != permAssignment.end()) {
                std::string s = int2string(it->second);
                std::cout << "\033[1m\033[31m" << s << "\033[0m ";
            } else {
                std::map<Coord, int>::iterator itt = assignment.find(c);
                if (itt != assignment.end()){
                    std::string s = int2string(itt->second);
                    std::cout << "\033[1m\033[33m" << s << "\033[0m ";
                } else {
                    std::cout << "\033[37m0 \033[0m";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Press anything to continue \n";
}

std::string Soduku::int2string(int n)
{
    std::string result;
    std::ostringstream oss;
    oss << n;
    result = oss.str();
    return result;
}

void Soduku::printGridDomains()
{
    for (std::map<Coord, Set<int>>::iterator i = grid.begin();
        i != grid.end(); i++) {
        std::cout << i->first << " => ";
        i->second.print();
        std::cout << std::endl;
    }
}
void Soduku::printAssignmentGridDomains()
{
    for (std::map<Coord, int>::iterator i = assignment.begin();
        i != assignment.end(); i++) {
        std::cout << i->first << " => ";
        grid[i->first].print();
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