#ifndef SODUKU_GENERATOR_H
#define SODUKU_GENERATOR_H
#include <vector>
#include "Soduku.h"
class Soduku_Generator : public Soduku
{
	public:
		Soduku_Generator(std::string = "medium", int = 9);
		void print_puzzle();
		void write_puzzle(std::string, int);
	private:
		std::vector<int> *get_shuffled_numbers();
		void init_blank_puzzle();
		bool search();
		bool search(Coord);
		bool satisfies_constraints(int, Coord);
		Coord next_coord(Coord);
		void make_puzzle(std::string);
		bool eliminate_one_value();
};
#endif