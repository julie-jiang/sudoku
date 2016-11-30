#include <iostream>
#include <fstream>
#include <vector>
#include "Soduku_Generator.h"
#include "Coord/Coord.h"
#include "Soduku_Util.h"

Soduku_Generator::Soduku_Generator(std::string difficulty, int size)
{
	gridSize = size;
	n = square_root(gridSize);
	init_blank_puzzle();
	while (not search()) {}  // Loop until we find completed soduku puzzle
	make_puzzle(difficulty); // Randomly eliminate some variables
}
bool Soduku_Generator::search()
{
	// initial coordinates
	Coord c(0, 0);
	return search(c);
}
void Soduku_Generator::write_puzzle(std::string directory, int index)
{
    // Open file
    std::string filename = directory + "/puzzle" + int2string(index) + ".txt";
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
			outFile << number << whitespace[get_num_digits(number) - 1];
        } outFile << std::endl;
    }
    outFile.close();
    delete [] whitespace;
    
}

void Soduku_Generator::print_puzzle()
{
	int max_char_length = get_num_digits(gridSize);
    std::string *whitespace = get_whitespaces(max_char_length);
	for (size_t i = 0; i < gridSize; i++) {
		if (i % n == 0) {
            print_horizontal_line(max_char_length);
        }
        std::cout << "| ";
		for (size_t j = 0; j < gridSize; j++) {
			Coord c(i, j);
			int number = (*puzzle)[c];
			if (number == 0) {
				std::cout << "\033[1m\033[31m0\033[0m" << whitespace[get_num_digits(number) - 1];
			} else {
				std::cout << number << whitespace[get_num_digits(number) - 1];
			}
			if ((j + 1) % n == 0) {
                std::cout << "| ";
            }
		} 
		std::cout << std::endl;
	}
	print_horizontal_line(max_char_length);
    delete [] whitespace;
}

void Soduku_Generator::make_puzzle(std::string difficulty)
{
	// eliminate roughly 80% of all the variables if difficulty is hard, 50% if 
	// difficulty is medium, and 30% is the difficulty is easy.
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
		while (not eliminate_one_value()){}
	}
}
bool Soduku_Generator::eliminate_one_value()
{
	int x = rand() % gridSize;
	int y = rand() % gridSize;
	Coord c(x, y);
	if ((*puzzle)[c] != 0) {
		(*puzzle)[c] = 0;
		return true;
	}
	return false;
}
bool Soduku_Generator::search(Coord c)
{
	if (c[1] == (int) gridSize) { // base case if c is the dunmy coord
		return true;
	}
	std::vector<int> *numbers = get_shuffled_numbers();
	for (size_t k = 0; k < gridSize; k++) {
		if (satisfies_constraints((*numbers)[k], c)) {
			(*puzzle)[c] = (*numbers)[k];
		
			if (search(next_coord(c))) {
				delete numbers;
				return true;
			}
		}
			
	}
	delete numbers;
	return false;
}
Coord Soduku_Generator::next_coord(Coord c)
{
	int x = c[0];
	int y = c[1];
	if (x < (int) gridSize - 1) {
		Coord next_c(x + 1, y);
		return next_c;
	}
	Coord next_c(0, y + 1);
	return next_c;
}
bool Soduku_Generator::satisfies_constraints(int value, Coord c)
{
	int x = c[0];
	int y = c[1];
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
	return true;
}
void Soduku_Generator::init_blank_puzzle()
{
	for (size_t i = 0; i < gridSize; i++) {
		for (size_t j = 0; j < gridSize; j++) {
			Coord c(i, j);
			puzzle->insert(c, 0);
		}
	}
}
/* Fisher-Yates shuffle algorithm */
std::vector<int> *Soduku_Generator::get_shuffled_numbers()
{
	// Make new vector {1, 2, 3, ..., gridSize - 1} 
	std::vector<int> *numbers = new std::vector<int>;
	for (int i = 1 ; i <= (int) gridSize; i++) {
		numbers->push_back(i);
	}
	// Shuffle by iterating backwards
	for (size_t i = gridSize - 1; i > 0; i--) {
		size_t j = rand() % i;			// Choose index j such that 0 <= j < i
		(*numbers)[i] ^= (*numbers)[j]; // Swap them using bitwise operation
		(*numbers)[j] ^= (*numbers)[i];
		(*numbers)[i] ^= (*numbers)[j];
	}
	return numbers;
}
