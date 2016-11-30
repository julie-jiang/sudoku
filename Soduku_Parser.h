/* 
 * Soduku_Parser.h
 * Header file for the class Soduku_Parser.cpp.
 * Parses command line arguments for the soduku program.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* 
 * Parses the command line inputs for the soduku program. The possible commands
 * are as follows:
 * Usage: ./soduku [--solve     or -s  <filename>] \
 *                 [--solve-all or -sa <filelist>] \
 *                 [--check     or -c  <filename>] \
 *                 [--check-all or -ca <directory>] \
 * 
 * Mandatory Argument (must provide one and only one of the following):
 * --solve      or -s  Solve a single Soduku puzzle. 
 *                     Provide path to a unsolved Soduku puzzle.
 * --solve-all  or -sa Solve all Soduku puzzles. 
 *                     Provide path to a list of paths to unsolved Soduku puzzles
 * --check      or -c  Check the validity of a single Soduku puzzle. 
 *                     Provided path to a unsolved Soduku puzzle.
 * --check-all  or -ca Check the validity of all solved Soduku puzzles. 
 *                     Provide path to a list of paths to solved Soduku puzzles.
 * 
 * Optional Arguments for --solve or --solve-all:
 * --write or -w   Write solution files to the specified directory.
 * --hide  or -h   Disable the default setting that print solutions to console.
 * 
 * Default settings:
 * write = false and print = true
 */
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

		/* Only one of the following four booleans should be true */
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