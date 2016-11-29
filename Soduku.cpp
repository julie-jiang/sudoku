/* 
 * Soduku.cpp
 * Implementations of the Soduku class.
 * 
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                               Abstract                                    */
/*****************************************************************************/
/*
 * This is a useless class on its own. Therefore the default constructor has 
 * been made private. The classes Soduku_Solver and Soduku_Checker are derived
 * classes of this class. Soduku_Solver solves a given soduku puzzle; 
 * Soduku_Checker checks the validity of a solved puzzle. Please refer to them 
 * for more usage information.
 *
 * This class holds functions that are shared between Soduku_Solver and 
 * Soduku_Checker.
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <cassert>
#include "Soduku.h"
#include "Set/Set.h"
#include "Coord/Coord.h"
#include "HashMap/HashMap.h"


/*****************************************************************************/
/*                         Initialization Functions                          */
/*****************************************************************************/
/*
 * Process the input file and convert it into a Soduku puzzle.
 * Throw logic error if the file cannot be opened, or if the file does not 
 * contain a valid Soduku puzzle.
 */
void Soduku::read_puzzle()
{
    size_t num_elements = 0;
    // Open file 
    std::ifstream inFile;
    inFile.open(puzzle_name);
    if (inFile.fail()) {
        throw std::logic_error("ERROR: File " + puzzle_name + " does not exist");
    }

    // Read input
    std::queue<int> *elements = new std::queue<int>;
    std::string s;
    while (inFile >> s) {
        elements->push(string2int(s));
        num_elements++;
    }
    inFile.close();
    // Get grid size
    gridSize = square_root(num_elements);
    n = square_root(gridSize);

    // Initialize Soduku puzzle grid
    init_grid(*elements);
    delete elements;
}
/*
 * Initialize grid. 
 * "puzzle" maps a set of coordinates to their initial value as given in the 
 * soduku puzzle, be it 0 or 1-9.
 * "domains" maps a set of coordinates to their remaining legal domain values.
 * Here, this is initialized to be all the numbers from 1 to gridSize.
 */
void Soduku::init_grid(std::queue<int> &elements)
{
    // initialize grid
    for (size_t j = 0; j < gridSize; j++) {
        for (size_t i = 0; i < gridSize; i++) {
            Coord c(i, j);
            int num = elements.front();
            elements.pop();
            puzzle.insert(c, num);
            ;
        }
    }
}

/*****************************************************************************/
/*                           Utility Functions                               */
/*****************************************************************************/


/*
 * Find the square root of the given number. 
 * Throw logic error if no perfect square root can be found.
 */
size_t Soduku::square_root(size_t num)
{
    size_t i = 1;
    while (i <= num / 2 + 1) {
        if (i * i == num) {
            return i;
        }
        if (i * i > num) {
            break;
        }
        i++;
    }
    throw std::logic_error("Error: File " + puzzle_name + 
                           " does not contain valid Soduku puzzle");
}
/*
 * Convert a string to an int. 
 * Throw runtime error if the string is not numerical.
 */
int Soduku::string2int(std::string s)
{
    std::stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw std::logic_error("ERROR: File " + puzzle_name + 
                                 " contains nonnumerical value");

    return result;
}


/*
 * Make a new set of units that contains one of every possible value.
 * Return a pointer to this new set.
 */
Set<int> *Soduku::new_unit()
{
    Set<int> *one_unit = new Set<int>;
    for (int i = 1; i <= (int) gridSize; i++) {
        one_unit->add(i);
    }
    return one_unit;
}


