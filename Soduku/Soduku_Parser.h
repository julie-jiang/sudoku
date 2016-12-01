/* 
   Soduku_Parser.h
   Header file of the class Soduku_Parser.cpp.
   Parses command line arguments for the soduku program.
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/*
Usage: ./soduku [--solve     or -s  <filename>] \
                [--solve-all or -sa <filelist>] \
                [--check     or -c  <filename>] \
                [--check-all or -ca <filelist>] \
                [--generate  or -g  <some number>]

Mandatory flags (must provide one and only one of the following FIRST):
--solve      or -s  <filename>
                    Solve a single Soduku puzzle. 
                    Provide path to a unsolved Soduku puzzle.
--solve-all  or -sa <filelist>
                    Solve all Soduku puzzles. 
                    Provide path to a list of paths to unsolved Soduku puzzles
--check      or -c  <filename>
                    Check the validity of a single Soduku puzzle. 
                    Provided path to a unsolved Soduku puzzle.
--check-all  or -ca <filelist>
                    Check the validity of all solved Soduku puzzles. 
                    Provide path to a list of paths to solved Soduku puzzles.
--generate   or -g  <some number>
                    Generate one or many Soduku puzzle, depending on the next 
                    integer argument provided. If no subsequent argument is 
                    provided or if the next argument is a flag, then the number 
                    of puzzles to be generated will default to 1.
--help       or -h  See more usage information.

Optional flags for --solve, --solve-all or --generate:
--write      or -w   <directory>
                    Write puzzle to the specified directory as a .txt file.
--hide       or -h  Disable the default setting that print puzzle to console.

More optional flags for --generate:
--difficulty or -d  <level>
                    Generate either "hard", "medium" or "easy" soduku puzzles.
                    Default setting is "medium".
--size       or -n  <some number>
                    Generate a puzzle based on the given size. E.g. if the 
                    argument is 16, then a 16 by 16 Soduku puzzle will be 
                    generated. This number must be a perfect square.
                    Default setting is 9.
 
 Default settings:
 write = false, print = true, num_generate = 1, generate_difficulty = "medium" 
 and generate_size = 9 */
 
#ifndef SODUKU_PARSER_H
#define SODUKU_PARSER_H
#include <string>
class Soduku_Parser {
	public:
		/* Parse command line input */
		Soduku_Parser(int, char **); 

		/* Print usage with cerr */
		static void help_message();

		/* Stores input and output paths to soduku puzzles */
		std::string input_path;
		std::string output_path;

		/* Only one of the following five booleans should be true */
		bool solve_one; 
		bool solve_all;
		bool check_one;
		bool check_all;
		bool generate;

		/* Variables for the generate option */
		int num_generate;
		int generate_size;
		std::string generate_difficulty;


		/* write defaults to false and print defaults to true */
		bool write;
		bool print;
	private:

		void parse_first_flag(std::string);
		void parse_optional_flags(int, int, char **);
		void init_default_settings();
		void print_usage();


};
#endif