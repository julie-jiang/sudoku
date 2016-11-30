#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "Soduku_Generator.h"
#include "Coord/Coord.h"

Soduku_Generator::Soduku_Generator()
{
	gridSize = 9;
	n = square_root(gridSize);
	init_blank_puzzle();
	srand(time(NULL));
	Coord c(0, 0); // initial coordinates
	if (search(c)) {
		std::cout << "puzzle found!\n";
	} else {
		std::cout << "puzzle not found\n";
	}
	print_puzzle();
	make_puzzle();
	print_puzzle();
}
void Soduku_Generator::make_puzzle()
{
	int num_eliminate = 40;
	for (int i = 0; i < num_eliminate; i++) {
		while (not eliminate_one_value()){}
	}
}
bool Soduku_Generator::eliminate_one_value()
{
	int x = rand() % gridSize;
	int y = rand() % gridSize;
	Coord c(x, y);
	if (puzzle[c] != 0) {
		puzzle[c] = 0;
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
			puzzle[c] = (*numbers)[k];
		
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
		if (i != x and puzzle[c1] == value) { // check row
			return false;
		}
		if (i != y and puzzle[c2] == value) { // check column
			return false;
		}
	}
	// check subgrid
	int i_begin = x - x % n; int i_end = x - x % n + n;
	int j_begin = y - y % n; int j_end = y - y % n + n;
	
	for (int i = i_begin; i < i_end; i++) {
		for (int j = j_begin; j < j_end; j++) {
			Coord c3(i, j);
			if (c3 != c and puzzle[c3] == value) {
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
			puzzle.insert(c, 0);
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
void Soduku_Generator::print_puzzle()
{
	for (size_t i = 0; i < gridSize; i++) {
		for (size_t j = 0; j < gridSize; j++) {
			Coord c(i, j);
			if (puzzle[c] == 0) {
				std::cout << "\033[1m\033[31m0\033[0m ";
			} else {
				std::cout << puzzle[c] << " ";
			}
		} 
		std::cout << std::endl;
	}
	std::cout << std::endl;

}