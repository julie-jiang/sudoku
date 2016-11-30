/* 
   Soduku_Generator.cpp
   Implementations for the Soduku_Generator class, a class derived from Soduku.
   Generates a random Soduku puzzle on the fly.
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* To generate a Soduku puzzle of size puzzle_size and difficulty 
   puzzle_difficulty:
        Soduku_Generator soduku(puzzle_difficulty, puzzle_size);
   
   Difficulty is a string that is "hard", "medium", or "easy".
   Size is a integer specifying the size of the soduku puzzle. It must
   be a perfect square of some other integer, due to the way soduku 
   puzzles are defined.

   These parameters can be omitted, in which case difficulty will default to 
   "medium" and size will default to 9.

   To view the puzzle in terminal:
        soduku.print_puzzle();
   To write the puzzle to the directory mypuzzles and title it puzzle1.txt:
        soduku.write_puzzle(mypuzzles, 1); */
#include <iostream>
#include <fstream>
#include <vector>
#include "Soduku_Generator.h"
#include "../Coord/Coord.h"
/*****************************************************************************/
/*                             Public Functions                              */
/*****************************************************************************/
/* Parameterized constructor. 
   Parameters: 
        1) difficulty is a string that is "hard", "medium", or "easy".
        2) size is a perfect square of some other integer.
   If the parameters are do not satisfy these requirements, logic error will be
   thrown. These arguments can be omitted, in which case difficulty will 
   default to "medium" and size will default to 9.
   A playable soduku puzzle will be constructed at the end of this constructor.
   It rests in "puzzle". */
Soduku_Generator::Soduku_Generator(std::string difficulty, int size)
{
    gridSize = size;
    n = square_root(gridSize);
    container_size = gridSize * gridSize;

    // Search for a valid soduku puzzle
    search_puzzle(); 
    // Make a playable puzzle by randomly eliminate some variables
    make_puzzle(difficulty); 
}
/* Print the generated soduku puzzle as a 2D grid via standard cout. 
   The Coords that don't have assigned values will be printed as '0' in
   bold red. This is printed with gridlines!  */
void Soduku_Generator::print_puzzle()
{
    int max_char_length = get_num_digits(gridSize);
    std::string *whitespace = get_whitespaces(max_char_length);
    for (size_t i = 0; i < gridSize; i++) {
        if (i % n == 0) {
            print_horizontal_line(max_char_length);
        } std::cout << "| ";
        for (size_t j = 0; j < gridSize; j++) {
            Coord c(i, j);
            int number = (*puzzle)[c];
            (number == 0) ?  std::cout << "\033[1m\033[31m0\033[0m" 
                          :  std::cout << number;
            // Print enough whitespaces so that all the numbers line up nicely
            std::cout << whitespace[get_num_digits(number) - 1];
            if ((j + 1) % n == 0) {
                std::cout << "| ";
            }
        } 
        std::cout << std::endl;
    }
    print_horizontal_line(max_char_length);
    delete [] whitespace;
}
/* Write the generated soduku puzzle as a 2D grid to a file called "puzzle" + 
   index + ".txt" in the specified directory. The puzzle will be written 
   without gridlines and with "0" in place of any Coords with indeterminate
   value.  
   The parameter index is optional. If it is omitted, then index will be an 
   empty string. */
void Soduku_Generator::write_puzzle(std::string directory, std::string index)
{
    // Open file
    std::string filename = directory + "/puzzle" + index + ".txt";
    std::ofstream outFile(filename);
    if (not outFile.is_open()) {
        throw std::logic_error("ERROR: " + directory + 
                               " is not a valid directory");
    }
    // Write to file
    int max_char_length = get_num_digits(gridSize);
    std::string *whitespace = get_whitespaces(max_char_length);
    for (size_t j = 0; j < gridSize; j++) {
        for (size_t i = 0; i < gridSize; i++) {
            Coord c(i, j);
            int number = (*puzzle)[c];
            // Print enough whitespaces so that all the numbers line up nicely
            outFile << number << whitespace[get_num_digits(number) - 1];
        } outFile << std::endl;
    }
    outFile.close();
    delete [] whitespace;
    
}
/*****************************************************************************/
/*                        Puzzle searching Functions                         */
/*****************************************************************************/
/* Loops until a valid soduku puzzle is found.
   Starts off by clearing the grid. */
void Soduku_Generator::search_puzzle()
{
    Coord c(0, 0); // initial coordinates
    do {
        init_blank_puzzle();
    } while (not search_puzzle(c));
}
/* Recursively search for a soduku puzzle with a depth-first backtracking 
   search algorithm. In each recursion, find a viable value for this Coord 
   given the existing constraints. 
   Returns false if no legal value can be found */
bool Soduku_Generator::search_puzzle(Coord c)
{
    // Base case if c is the dummy coord. This signals that all the Coords
    // in the puzzle has been filled with a legal value. We can return true.
    if (c[1] == (int) gridSize) { 
        return true;
    }
    // Get the numbers from 1 to gridSize in random order. 
    std::vector<int> *numbers = get_shuffled_numbers();
    Coord next_c = next_coord(c); // The next Coord that needs to be filled.
    for (size_t k = 0; k < gridSize; k++) {  // Try them one by one.
        if (satisfies_constraints((*numbers)[k], c)) {
            (*puzzle)[c] = (*numbers)[k];

            // Depth first search
            if (search_puzzle(next_c)) {
                delete numbers;
                return true;
            } // If it didn't work, backtrack by trying the next value.
        }
    }
    delete numbers;
    // Nothing worked! Return false.
    return false; 
}
/* Returns true if assigning this value to this Coord c does not violate 
   any existing constraints.
   Checks all the other Coords in c's row, column and subgrid to see that
   that are not assigned to this value. */
bool Soduku_Generator::satisfies_constraints(int value, Coord c)
{
    int x = c[0]; int y = c[1];
    for (int i = 0; i < (int) gridSize; i++) {
        Coord c1(i, y); Coord c2(x, i);
        if (i != x and (*puzzle)[c1] == value) { // check row
            return false;
        }
        if (i != y and (*puzzle)[c2] == value) { // check column
            return false;
        }
    }
    // check subgrid
    int i_begin = x - x % n; int i_end = x - x % n + n;
    int j_begin = y - y % n; int j_end = y - y % n + n;
    
    for (int i = i_begin; i < i_end; i++) {
        for (int j = j_begin; j < j_end; j++) {
            Coord c3(i, j);
            if (c3 != c and (*puzzle)[c3] == value) {
                return false;
            }
        }
    }
    return true; // All constraints check out! 
}
/* Generate the next Coord to check. If not at the end of a row, generate
   The Coord (x + 1, y). Else, generate (0, y + 1).
   If the given Coord is (gridSize - 1, gridSize - 1), meaning it is the
   last Coord in the puzzle, then the Coord (0, gridSize) will be returned.
   This Coord does not actually exist in the puzzle. Therefore it serves as
   a sentinel. 
 */
Coord Soduku_Generator::next_coord(Coord c)
{
    int x = c[0]; int y = c[1];
    if (x < (int) gridSize - 1) {
        Coord next_c(x + 1, y);
        return next_c;
    }
    Coord next_c(0, y + 1);
    return next_c;
}

/* Construct a vector consisting of the values from 1 to gridSize, and then
   randomly shuffle them. 
   This utilizes the Fisher-Yates shuffle algorithm */
std::vector<int> *Soduku_Generator::get_shuffled_numbers()
{
    // Make new vector {1, 2, 3, ..., gridSize} 
    std::vector<int> *numbers = new std::vector<int>;
    for (int i = 1 ; i <= (int) gridSize; i++) {
        numbers->push_back(i);
    }
    // Shuffle by iterating backwards
    for (size_t i = gridSize - 1; i > 0; i--) {
        size_t j = rand() % i;          // Choose index j such that 0 <= j < i
        (*numbers)[i] ^= (*numbers)[j]; // Swap them using bitwise operation
        (*numbers)[j] ^= (*numbers)[i];
        (*numbers)[i] ^= (*numbers)[j];
    }
    return numbers;
}
/*****************************************************************************/
/*                           Puzzle Making Functions                         */
/*****************************************************************************/

/* Make a playable puzzle by randomly eliminating values from the puzzle. 
   Assumes that the puzzle is complete to begin with (i.e. all Coords have
   an assigned value).
   Eliminates roughly 80% of all the variables if difficulty is hard, 50% if 
   difficulty is medium, and 30% is the difficulty is easy. */
void Soduku_Generator::make_puzzle(std::string difficulty)
{
    // Get the number of values to eliminate based on difficulty. 
    int num_eliminate;
    if (difficulty == "hard") {         
        num_eliminate = (gridSize * gridSize) * 4 / 5; 
    } else if (difficulty == "medium") {
        num_eliminate = (gridSize * gridSize) / 2;
    } else if (difficulty == "easy") {
        num_eliminate = (gridSize * gridSize) * 3 / 10;
    } else {
        throw std::logic_error("ERROR: " + difficulty + " is not a valid " 
                               "difficulty option.");
    }
    for (int i = 0; i < num_eliminate; i++) {
        eliminate_one_value();
    }
}
/* Eliminates a value from the puzzle. This is done by randomly generating
   a Coord and then set it to zero. Make sure that the new Coord is not 
   already set to zero. 
 */
void Soduku_Generator::eliminate_one_value()
{
    // Loop until a new value has been set to zero
    while (true) {
        int x = rand() % gridSize; int y = rand() % gridSize;
        Coord c(x, y);
        if ((*puzzle)[c] != 0) {
            (*puzzle)[c] = 0;
            break;
        }
    }
}

/*****************************************************************************/
/*                               Initialization                              */
/*****************************************************************************/
/* Initialize a blank soduku puzzle by setting all the Coords to zero. */
void Soduku_Generator::init_blank_puzzle()
{
    puzzle = new HashTable<Coord, int>(container_size);
    for (size_t i = 0; i < gridSize; i++) {
        for (size_t j = 0; j < gridSize; j++) {
            Coord c(i, j);
            puzzle->insert(c, 0);
        }
    }
    
}

