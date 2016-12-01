/* 
 * Soduku_Solver.h
 * Header file of the Soduku_Solver class, a class derived from Soduku.
 * This class can solve a soduku puzzle of any size.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* To solve a puzzle, create an instance of Soduku with the parametrized 
   constructor, and provide a path to a file that contains an unsolved soduku 
   puzzle:
        Soduku soduku(puzzle.txt);
   To print the (complete or incomplete) solutions to terminal:
        soduku.print();
   To output the solutions to a file:
        soduku.write(filename.txt);
   For both of these options, if the puzzle is only partially solved, then
   grid cells with indeterminate values will be printed as bold red '0'.
 */
#ifndef SODUKU_SOLVER_H
#define SODUKU_SOLVER_H
#include "Soduku.h"
#include "../Coord/Coord.h"
#include "../HashTable/HashTable.h"
#include "../Set/Set.h"
class Soduku_Solver: public Soduku {
    public:
        /* Solve a puzzle given in the provided file.
           If the second parameter is true, the the process of solving
           the puzzle will be shown. */
        Soduku_Solver(std::string, bool);
        ~Soduku_Solver();

        /* Print the solved or partially solved puzzle. */
        void print_solution();

        /* Write the solved or partially solved puzzle to the specified 
           directory. */
        void write_solution(std::string);
        
    private:
        /* Private Variables */
        HashTable<Coord, std::vector<std::vector<Coord>>> *units;
        HashTable<Coord, Set<Coord>> *peers;
        HashTable<Coord, Set<int>> domains;
        /* Default constructor made private so it can't be called */
        Soduku_Solver() {} 

        /* Solve functions */
        bool solve();
        bool prune_grid();
        bool search(HashTable<Coord, Set<int>> &);
        bool solved(HashTable<Coord, Set<int>> &);
        Coord select_unassigned_Coord(HashTable<Coord, Set<int>> &);
        bool assign(HashTable<Coord, Set<int>> &, Coord, int);
        bool eliminate(HashTable<Coord, Set<int>> &, Coord, int);
        bool eliminate_from_peers(HashTable<Coord, Set<int>> &, Coord);
        bool check_unique_remaining_values(HashTable<Coord, Set<int>> &, 
                                           Coord, int);

        /* Other init/helper functions */
        void init_containers();
        void init_containers1(std::vector<std::vector<Coord>> &);
        void init_containers2(std::vector<std::vector<Coord>> &);
        void init_containers3(std::vector<std::vector<Coord>> &);
        void printDomains(HashTable<Coord, Set<int>> &);
        void print_solution(HashTable<Coord, Set<int>> &);
};
#endif