/* 
 * Soduku_Checker.h
 * Header file of the Soduku_Checker class, a class derived from Soduku.
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
 *      bool result = soduku.check_solution(solutions.txt);
 * Result is true if the solution is valid.
 */
#ifndef SODUKU_CHECKER_H
#define SODUKU_CHECKER_H
#include "Soduku.h"
class Soduku_Checker: public Soduku {
	public:
        Soduku_Checker() : Soduku() {}
        
        // Checks the validity of the puzzle in the given file
		bool check_solution(std::string); 
	private:
		bool check_rows_columns();
		bool check_subgrid();

};
#endif