/*
 * Header file for the Soduku class.
 * This class can solve a soduku puzzle of any size.
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* First create an instance of Soduku:
 *              Soduku soduku;
 * Solve a puzzle:
 *      Provide a path to a file that contains an unsolved soduku puzzle: 
 *              soduku.solve(puzzle.txt);
 *      To see the solutions:
 *              soduku.print();
 *      Or output the solutions to a file:
 *              soduku.write(filename.txt);
 *      For both of these options, if the puzzle is only partially solved, then
 *      grid cells with indeterminate values will be printed as bold red '0'.
 *
 * Check the validity of a puzzle:
 *      Provide a path to a file that contains a (maybe) solved soduku puzzle:
 *          bool result = soduku.check(puzzle_solutions.txt);
 * 
 */
#ifndef SODUKU_H
#define SODUKU_H
#include <cstdlib>
#include <vector>
#include <queue>
#include "Set/Set.h"
#include "Coord/Coord.h"
#include "HashMap/HashMap.h"

class Soduku {
    public:
        Soduku() {}
        ~Soduku() {}
        void solve(std::string);
        bool check(std::string);
        /* 
         * Print the solutions (complete or imcomplete) to the given puzzle.
         */
        void print();

        /*
         * Write the solutions to the specified directory.
         */
        void write(std::string);
        
    private:
        /* Private variables */
        // TODO: Hashmap size?!
        HashMap<Coord, std::vector<std::vector<Coord>>> units;
        HashMap<Coord, Set<Coord>> peers;
        HashMap<Coord, Set<int>> domains;
        HashMap<Coord, int> puzzle;
        std::string puzzle_name;
        size_t gridSize;
        size_t n;

        /* Puzzle solving functions */
        bool solve();
        bool prune_grid();
        bool search(HashMap<Coord, Set<int>> &);
        bool solved(HashMap<Coord, Set<int>> &);
        Coord select_unassigned_variable(HashMap<Coord, Set<int>> &);
        bool assign(HashMap<Coord, Set<int>> &, Coord, int);
        bool eliminate(HashMap<Coord, Set<int>>&, Coord, int);
        bool eliminate_from_peers(HashMap<Coord, Set<int>> &, Coord);
        bool check_unique_remaining_values(HashMap<Coord, Set<int>> &, Coord, int);

        bool validate_puzzle();

        /* Initialiation functions */
        void init();
        void reset();
        void read_puzzle();
        void init_grid(std::queue<int> &);
        void init_data_structures();
        
        /* Utility functions */
        int string2int(std::string);
        size_t square_root(size_t);
        void printDomains(HashMap<Coord, Set<int>> &);
        void print_horizontal_line(int);
        int get_num_digits(int);
        std::string *get_whitespaces(int);
        Set<int> *new_unit();
        


        


};
#endif