#ifndef SODUKU_GENERATOR_H
#define SODUKU_GENERATOR_H
#include <vector>
#include "Soduku.h"
class Soduku_Generator : public Soduku
{
	public:
		Soduku_Generator();
	private:
		std::vector<int> *get_shuffled_numbers();
		void print_puzzle();
		void init_blank_puzzle();
		bool search(Coord);
		bool satisfies_constraints(int, Coord);
		Coord next_coord(Coord);
		void make_puzzle();
		bool eliminate_one_value();
};
#endif