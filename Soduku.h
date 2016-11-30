/* 
 * Soduku.h
 * Header file for the Soduku class.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                  Blurb                                    */
/*****************************************************************************/
/* This is a useless class on its own. The classes Soduku_Solver,
   Soduku_Checker, and Soduku_Generator are derived classes of this class. 
   Soduku_Solver solves a given soduku puzzle
   Soduku_Checker checks the validity of a solved puzzle. 
   Soduku_Generator generates a valid soduku puzzle. 
   Please refer to them for more usage information.

   This class holds methods and variables that are shared amongst Soduku_Solver 
   and Soduku_Checker, and Soduku_Generator. These are mostly utility and 
   initialization methods.                                                    
*/

#ifndef SODUKU_H
#define SODUKU_H
#include <cstdlib>
#include <vector>
#include <queue>
#include "Set/Set.h"
#include "Coord/Coord.h"
#include "HashTable/HashTable.h"

// Everything is protected
class Soduku { 
    
    protected:
        // variables
        HashTable<Coord, int> puzzle;
        std::string puzzle_name;
        size_t gridSize;
        size_t n;

        // Initialiation functions 
        void read_puzzle();
        void init_grid(std::queue<int> &);
        
        
        // Utility functions 
        size_t square_root(size_t);
        Set<int> *new_unit();
        int get_num_digits(int);
        std::string *get_whitespaces(int);
        void print_horizontal_line(int);

};
#endif