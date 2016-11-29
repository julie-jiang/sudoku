/* 
 * Soduku_Checker.cpp
 * Implementations for the Soduku_Checker class, a class derived from Soduku.
 * Checks whether a solution to a Soduku puzzle is valid. It can check Soduku
 * puzzles of arbitrary size.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/*
 * To check the validity of a Soduku puzzle that rests in the file 
 * solutions.txt:
 *      Soduku_Checker soduku;
 *      bool result = soduku.check(solutions.txt);
 * Result is true if the solution is valid.
 */
#include "Soduku_Checker.h"
#include "Coord/Coord.h"
#include "Set/Set.h"
/*****************************************************************************/
/*                           Implementations                                 */
/*****************************************************************************/
/*
 * Validate the puzzle stored in 'puzzle'. This is done checking to see that 
 * each unit in the puzzle contains one and only one of the values from 1 to
 * gridSize. A unit is defined to be a row, column or a subgrid of size n by n.
 *
 * Here an important helper function used is new_unit(), which builds a new 
 * Set that contains one of all the values from 1 to gridSize.
 *
 * Returns true if puzzle is valid. 
 */
bool Soduku_Checker::check(std::string filename)
{
    puzzle_name = filename;
    read_puzzle();
    return(check_rows_columns() and check_subgrid());
}
/* 
 * Returns true if all row and column units contain one and only one of the 
 * values from 1 to gridSize. 
 */
bool Soduku_Checker::check_rows_columns()
{
    // Check that each row and column contains one and only one of the 
    // values from 1 to gridSize
    for (size_t j = 0; j < gridSize; j++) {
        Set<int> *unit1 = new_unit();
        Set<int> *unit2 = new_unit();
        for (size_t i = 0; i < gridSize; i++) {
            Coord c1(i, j); Coord c2(j, i);
            // Contradiction if the value does not exist in the units
            if (not unit1->contains(puzzle[c1]) or 
                not unit2->contains(puzzle[c2]))
                return false;
            unit1->remove(puzzle[c1]);
            unit2->remove(puzzle[c2]);
        }
        // Contradiction if the units are not empty
        if (not unit1->empty() or not unit2->empty()) 
            return false;
        delete unit1; delete unit2;
    }
    return true;
}
/* 
 * Returns true if all subgrid units contain one and only one of the 
 * values from 1 to gridSize. 
 */
bool Soduku_Checker::check_subgrid()
{
    // Check that each subgrid contains one and only one of the values
    // from 1 to gridSize
    for (size_t i = 0; i < gridSize; i += n) {
        for (size_t j = 0; j < gridSize; j += n) {
            Set<int> *unit3 = new_unit();
            for (size_t k = i; k < n + i; k++) {
                for (size_t l = j; l < n + j; l++) {
                    Coord c3(l, k);
                    // Contradiction if the value does not exist in the subgrid
                    if (not unit3->contains(puzzle[c3])) 
                        return false;
                    unit3->remove(puzzle[c3]);
                }
            }
            // Contradiction if the units are not empty
            if (not unit3->empty()) 
                return false;
            delete unit3;
        }   
    }
    return true;
}
