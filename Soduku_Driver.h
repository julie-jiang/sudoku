/* 
 * Soduku_Driver.h
 * Header file for Soduku_Driver.cpp
 * Driver functions for the soduku class. Contains the solve_one, solve_all, 
 * check_one, and check_all functions, amongst other helper functions.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* 
 * A Soduku_Parser object must be provided to use the solve_one and/or 
 * solve_all functions. The check_one and check_all functions only require 
 * the path to the soduku puzzle or list of soduku puzzles.
 */
#ifndef SODUKU_DRIVER_H
#define SODUKU_DRIVER_H
#include "Soduku_Parser.h"

/*
 * Solves one puzzle contained in Soduku_Parser.input_path.
 * May print to terminal and may write to file.
 * Must be used with an Soduku_Parser object
 */
void solve_one(Soduku_Parser &);
/* 
 * Solves all soduku puzzles contained in Soduku_Parser.input_path
 * May print to terminal and may write to file. Also generates
 * a file that contains a list of paths to solution files if it will write 
 * solutions to files.
 * Must be used with an Soduku_Parser object
 */
void solve_all(Soduku_Parser &);
void solve_all_and_write(Soduku_Parser &); // solve all helper function

/*
 * Checks the validity of one soduku solution contained in the given 
 * input_file. Returns true if it is solved.
 */
bool check_one(std::string);

/*
 * Checks the validity of all soduku solutions contained in the files
 * indicated in the given input_file.
 * Returns true if all of them are solved.
 */
bool check_all(std::string);

#endif