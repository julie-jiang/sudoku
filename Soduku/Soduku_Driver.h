/* 
   Soduku_Driver.h
   Header file for Soduku_Driver 
   Driver class for the soduku class. Contains the solve_one, solve_all, 
   check_one, and check_all functions, amongst other helper functions.
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* This class must be used in conjunction with a Soduku_Parser object. 
   An instance of this class will be created in the main function 
   (in Soduku_Main.cpp) of the run_soduku program. 
   It contains all the driver functions for the run_soduku program.
 */
#ifndef SODUKU_DRIVER_H
#define SODUKU_DRIVER_H
#include "Soduku_Parser.h"

class Soduku_Driver
{
	public:
		/* Take one action. Calls one of solve_one, solve_all, check_one, 
		   check_all, and generate.  */
		Soduku_Driver(const Soduku_Parser &);

	private:
		
		/* Solves one puzzle contained in Soduku_Parser.input_path.
		   May print to terminal and may write to file.*/
		void solve_one(const Soduku_Parser &);
		/*  Solves all soduku puzzles contained in Soduku_Parser.input_path
		    May print to terminal and may write to file. Also generates
		    a file that contains a list of paths to solution files, if it will 
		    write solutions to files. */
		void solve_all(const Soduku_Parser &);
		void solve_all_and_write(const Soduku_Parser &); // helper function

		/* Checks the validity of one soduku solution contained in the file
		   parser.input_path. Results will be printed via standard cout. */
		void check_one(const Soduku_Parser &);

		/* Checks the validity of all soduku solutions contained in the files
   		   indicated in file parser.input_path.
   		   Results will be printed via standard cout. */
		void  check_all(const Soduku_Parser &);

		/* Generate one or many Soduku puzzle of size parser.generate_size. 
		   May print to terminal and may write to file.
		   If generating a single puzzle and writing to file, 
		   the file will be named puzzle.txt
		   Else if generating more than one puzzle and writing to file, 
		  then a file named puzzle_list.txt consisting of all the paths to the 
		   generated puzzles will be made. */
		void generate(const Soduku_Parser &);
		void generate_one(const Soduku_Parser &); // Helper functions
		void generate_all(const Soduku_Parser &);
		void generate_all_and_write(const Soduku_Parser &);
};
#endif