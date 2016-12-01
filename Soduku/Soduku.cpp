/* 
   Soduku.cpp
   Implementations of the Soduku class, a base class for Soduku_Solver, 
   Soduku_Checker, and Soduku_Generator.
   
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project 
*/
#include <iostream>
#include <fstream>
#include <queue>
#include "Soduku.h"
#include "Soduku_Util.h"
#include "../Set/Set.h"
#include "../Coord/Coord.h"
#include "../HashTable/HashTable.h"

/* Constructor. Initialize puzzle */
Soduku::Soduku()
{
    puzzle = nullptr;
}
/* Destructor */
Soduku::~Soduku() {
    delete puzzle;
}

/*****************************************************************************/
/*                         Initialization Functions                          */
/*****************************************************************************/
/*
 * Process the input file and convert it into a Soduku puzzle.
 * Throw logic error if the file cannot be opened, or if the file does not 
 * contain a valid Soduku puzzle.
 */
void Soduku::read_puzzle() {
    // Open file 
    std::ifstream inFile;
    inFile.open(puzzle_name);
    if (inFile.fail()) {
        throw std::logic_error("ERROR: File " + puzzle_name + " does not exist");
    }
    // Read input
    std::queue<int> *elements = new std::queue<int>;
    std::string s;
    size_t num_elements = 0;
    while (inFile >> s) {
        elements->push(string2int(s));
        num_elements++;
    }
    inFile.close();
    // Get sizes
    container_size = num_elements;
    gridSize = square_root(num_elements);
    n = square_root(gridSize);
    // Initialize Soduku puzzle grid
    init_grid(elements);
    delete elements;
}
/*
 * Initialize grid. 
 * "puzzle" maps a set of coordinates to their initial value as given in the 
 * soduku puzzle, be it 0 or 1-9.
 * "domains" maps a set of coordinates to their remaining legal domain values.
 * Here, this is initialized to be all the numbers from 1 to gridSize.
 */
void Soduku::init_grid(std::queue<int> *elements) {
    // initialize grid
    puzzle = new HashTable<Coord, int>(container_size);
    for (size_t j = 0; j < gridSize; j++) {
        for (size_t i = 0; i < gridSize; i++) {
            Coord c(i, j);
            int num = elements->front();
            elements->pop();
            puzzle->insert(c, num);
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
size_t Soduku::square_root(size_t num) {
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
 * Make a new set of units that contains one of every possible value.
 * Return a pointer to this new set.
 */
Set<int> *Soduku::new_unit() {
    Set<int> *one_unit = new Set<int>;
    for (int i = 1; i <= (int) gridSize; i++) {
        one_unit->add(i);
    }
    return one_unit;
}

/*
 * Based on the maximum number of digits (max_char_length) of the values 
 * in this puzzle, compute the number whitespaces needed for every value
 * so that a each value plus their associate whitespaces span the same
 * number of characters. 
 *
 * For example, if the largest possible value is 121, then max_char_length = 3.
 * Therefore numbers with one digits will be paired with 3 spaces, 
 * numbers with two digits will be paired with 2 spaces, and 
 * numbers with three digits will be paired with 1 space. 
 *      whitespace[0] = "   ";
 *      whitespace[1] = "  ";
 *      whitespace[2] = " ";
 * 
 * Returns a pointer to a array of strings of length max_char_length.
 */
std::string *Soduku::get_whitespaces(int max_char_length) {
    std::string *whitespace = new std::string [max_char_length];
    for (int i = 0; i < max_char_length; i++) {
        whitespace[i] = "";
        for (int j = i; j < max_char_length; j++) {
            whitespace[i] += " ";
        }
    }
    return whitespace;
}
/* Returns the number of digits in the given int */
int Soduku::get_num_digits(int num) {
    int i = 1;
    int digits = 1;
    while (num / i > 9) {
        i *= 10;
        digits++;
    }
    return digits;
}
/* Print helper function. Prints a horizontal line. */
void Soduku::print_horizontal_line(int max_char_length) {
    std::cout << "|";
    size_t length = gridSize * (max_char_length + 1) + n * 2 - 1;
    for (size_t i = 0; i < length; i++) {
        std::cout << "-";
    }
    std::cout <<"| \n";
}

