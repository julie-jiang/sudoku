/* 
   Soduku_Generator.cpp
   Implementations of the Soduku_Generator class, a class derived from Soduku.
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
#ifndef SODUKU_GENERATOR_H
#define SODUKU_GENERATOR_H
#include <vector>
#include "Soduku.h"
class Soduku_Generator : public Soduku {
    public:
        /* Parameterized constructor. The first parameter is the difficulty
           of the puzzle, which defaults to "medium". The second parameter
           is the size of the puzzle, which defaults to 9. If the third
           parameter is true, then the process of generating the puzzle 
           will be shown.
           A playable soduku puzzle will be constructed at the end of this 
           constructor. */
        Soduku_Generator(std::string = "medium", int = 9, bool = false);

        /* Print the generated soduku puzzle as a 2D grid */
        void print_puzzle();

        /* Write the generated soduku puzzle as a 2D grid to a file called 
           "puzzle" + index + ".txt" in the specified directory. 
           The second parameter index is optional. If it is omitted, then 
           index will be an empty string. */
        void write_puzzle(std::string, std::string = "");
    private:
        /* Puzzle searching functions */
        void search_puzzle();
        bool search_puzzle(Coord);
        bool satisfies_constraints(int, Coord);
        Coord next_coord(Coord);
        std::vector<int> *get_shuffled_numbers();
        
        /* Puzzle making functions */
        void make_puzzle(std::string);
        void eliminate_one_value();

        /* Initialization */
        void init_blank_puzzle();
};
#endif