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
/*  Usage: ./soduku [--solve     or -s  <filename>] \
                    [--solve-all or -sa <filelist>] \
                    [--check     or -c  <filename>] \
                    [--check-all or -ca <filelist>] \
                    [--generate  or -g  <some number>
   Default settings:
   write = false, print = true, num_generate = 1, 
   generate_difficulty = "medium", and generate_size = 9                     */
 
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


		bool write;          // defaults to false
		bool print;          // defaults to true
        bool show_process;   // defaults to false
	private:

		void parse_first_flag(std::string);
		void parse_optional_flags(int, int, char **);
		void init_default_settings();
		void print_usage();


};
#endif