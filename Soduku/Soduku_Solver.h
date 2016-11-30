/* 
 * Soduku_Solver.h
 * Header file for the Soduku_Solver class, a class derived from Soduku.
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
/*****************************************************************************/
/*                         Containers Explained                              */
/*****************************************************************************/
/* A Coord is an object that holds two integers that indicates the coordinates
   of a variable in a Soduku puzzle grid.
  
   A unit is defined to be a set of Coords a row, column, or subgrid. In a 
   typical 9 by 9 Soduku puzzle, there are 9 rows + 9 columns + 9 subgrids = 
   27 units. 
  
   The following containers will be used throughout Soduku_Solver:
  
   1. "allunits" is a vector of vector of Coords. It contains a list of all the
       units in the puzzle in terms of Coords.
   2. "units" is a map that maps a Coord to the three units that contains that
       Coord.
   3. "peers" is a map that maps a Coord to all the other Coords that share
      a common unit.
   4. "puzzle" is a map that maps a Coord to its initial value in the provided
      file. 
   5. "domains" is a map that maps a Coord to its remaining legal values. 
      Throughout the search algorithms, many different copies of "domains" will 
      be passed around so as to not get all the search states mixed up. There 
      is also a member variable called domains, which I will refer to as 
      this->domains.
 */
#ifndef SODUKU_SOLVER_H
#define SODUKU_SOLVER_H
#include "Soduku.h"
#include "../Coord/Coord.h"
#include "../HashTable/HashTable.h"
#include "../Set/Set.h"
class Soduku_Solver: public Soduku
{
	public:
        /* Solve a puzzle given in the provided file */
		Soduku_Solver(std::string);
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
        
        

        

};
#endif