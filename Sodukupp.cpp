#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <stack>
#include <math.h>
#include <cassert>
#include "AVLTree/AVLTree.h"
#include "Coord/Coord.h"
#include "Sodukupp.h"

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
                 std::cout << "\033[1m\033[31m" << values[c].getRoot() << "\033[0m ";
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
        std::cout << "solve(): at " << c << " d = " << d << std::endl;
		if (d != 0 and not assign(c, d)) {
            std::cout << "solve(): returning false because assignment " << c << " = " << d << " failed\n";
			return false;
        }
	}
	return true;
}
bool Soduku::assign(Coord c, int d)
{
    //std::cout << "trying to assign " << c << " to " << d << std::endl;
	AVLTree<int> *other_values = new AVLTree<int>;
	std::stack<int> domain = values[c].getElements();
	while (not domain.empty()) {
		int v = domain.top();
		domain.pop();
		if (v != d)
			other_values->add(v);
	}
	
	while (not other_values->empty()) {
		int d2 = other_values->pop();
		if (not eliminate(c, d2)) {
            std::cout << "assign(): returning false because eliminating " << d2 << " from " << c << " failed\n";
            
			return false;
		}
	}
    std::cout << ("\033[H\033[2J");
    //std::cout << "assigned " << c << " = " << d << std::endl;
    print();
	return true;
}
bool Soduku::eliminate(Coord c, int d)
{
    //std::cout << "eliminating " << d << " from " << c << std::endl;
    //values[c].print();
    //std::cout << std::endl;
	if (not values[c].contains(d)) {
		return true;
	}
	values[c].remove(d);
	if (values[c].empty()) {
        std::cout << "eliminate(): retruning false because values[c].empty() for c = "<< c << "\n";
		return false; // sanity check
	} else if (values[c].size() == 1) {
		int d2 = values[c].getRoot();
		std::stack<Coord> peeers = peers[c].getElements();
		while (not peeers.empty()) {
			Coord c2 = peeers.top();
			peeers.pop();
			if (not eliminate(c2, d2)) {
                std::cout << "eliminate(): returning false because eliminating " << d2 << " from " << c2 << " failed\n";
            
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
    //std::cout << "eliminating " << d << " from " << c << "successful!\n";
    
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
            values.insert(std::pair<Coord, AVLTree<int>>(c, AVLTree<int>()));
            for (int i = 1; i < gridSize + 1; i++) {
            	values[c].add(i);
            }
        }
    }
    assert(puzzle.size() == 81);
    assert(values.size() == 81);
    for (std::map<Coord, AVLTree<int>>::iterator i = values.begin();
    	 i != values.end(); i++) {
    	assert(i->second.size() == 9);
    }
        


}
void Soduku::init_data_structures()
{
	for (int j = 0; j < gridSize; j++) {
		allunits.push_back(std::vector<Coord>());
        for (int i = 0; i < gridSize; i++) {
            Coord c(i, j);
            grid.push_back(c);
            allunits[j].push_back(c);
            units.insert(std::pair<Coord, std::vector<std::vector<Coord>>>(c, std::vector<std::vector<Coord>>()));
            peers.insert(std::pair<Coord, AVLTree<Coord>>(c, AVLTree<Coord>()));
        }
    }
    for (int i = 0; i < gridSize; i++) {
    	allunits.push_back(std::vector<Coord>());
    	for (int j = 0; j < gridSize; j++) {
    		Coord c(i, j);
    		allunits[gridSize + i].push_back(c);

    	}
    }
    for (int i = 0; i < gridSize; i += n) {
    	for (int j = 0; j < gridSize; j += n) {
    		Coord c(i, j);
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
    /* tests */
    assert(grid.size() == 81);
    assert(allunits.size() == 27);
    
    for (int i = 0; i < (int) allunits.size(); i++) {
    	assert(allunits[i].size() == 9);
    	/*std::cout << "unit "<< i + 1 << ": " << std::endl;
    	for (int j = 0 ; j < (int) allunits[i].size(); j++) {
    		std::cout << allunits[i][j] << " ";
    	}
    	std::cout << std::endl;*/
    }
    assert(units.size() == 81);
    for (std::map<Coord, std::vector<std::vector<Coord>>>::iterator i = units.begin();
    	i != units.end(); i++) {
    	assert(i->second.size() == 3);
    	for (int j = 0; j < 3; j++) {
    		assert(i->second[j].size() == 9);
    	}
    	/*std::cout << "key = " << i->first << std::endl;
    	for (int j = 0; j < (int) i->second.size();j++ ) {
    		for (int k = 0; k < (int) i->second[j].size(); k++) {
    			std::cout << i->second[j][k] << ", ";
    		}
    		std::cout << std::endl;
    	}*/
    }
    assert(peers.size() == 81);
    for(std::map<Coord, AVLTree<Coord>>::iterator i = peers.begin();
    	i != peers.end(); i++) {
    	assert(i->second.size() == 20);
    	/*std::cout << i->first << "'s peers: " << std::endl;
    	i->second.print();
    	std::cout << std::endl;*/
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