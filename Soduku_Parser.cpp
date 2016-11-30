/* 
 * Soduku_Parser.cpp
 * Implementaion of the class Soduku_Parser.cpp.
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
#include <iostream>
#include <fstream>
#include <regex>
#include "Soduku_Parser.h"
Soduku_Parser::Soduku_Parser(int argc, char *argv [])
{
    // Initialize booleans
    solve_one = solve_all = check_one = check_all = write = false;
    print = true;
    // Must have at least 3 arguments
    if (argc < 3) {
        throw std::logic_error("ERROR: missing mandatory argument");
    }
    parse_first_argument(std::string(argv[1]));
    input_path = std::string(argv[2]);
    parse_optional_arguments(argc, argv);
}
/*
 * Parse the first argument and stores the input_path.
 */
void Soduku_Parser::parse_first_argument(std::string arg)
{
    std::regex solve_one_regex("--solve|-s");
    std::regex solve_all_regex("--solve-all|-sa");
    std::regex check_one_regex("--check|-c");
    std::regex check_all_regex("--check-all|-ca");
    std::regex generate_one_regex("--generate|-g");
    std::regex generate_all_regex("(--generate-|-ga-)[[:digit:]]+");
    if (std::regex_match(arg, solve_one_regex)) {
        solve_one = true;
    } else if (std::regex_match(arg, solve_all_regex)) {
        solve_all = true;
    } else if (std::regex_match(arg, check_one_regex)) {
        check_one = true;
    } else if (std::regex_match(arg, check_all_regex)) {
        check_all = true;
    } else if (std::regex_match(arg, generate_one_regex)) {
        std::cout << "matched generate_one\n";
        generate_one = true;
    } else if (std::regex_match(arg, generate_all_regex)) {
        std::cout << "matched generate_many\n";
        generate_many = true;
    } else {
        throw std::logic_error("ERROR: Invalid mandatory argument");
    }
}
/*
 * Parses any additional optional arguments
 */
void Soduku_Parser::parse_optional_arguments(int argc, char *argv[])
{
    int i = 3;
    while (i < argc) {
        std::string arg = argv[i];
        if ((arg == "--write" or arg == "-w") and i + 1 < argc) {
            write = true;
            output_path = argv[i + 1];
            i++;
        } else if (arg == "--hide" or arg == "-h") {
            print = false;
        } else {
            throw std::logic_error("ERROR: Unknown command line argument " + 
                                    arg);
        }
        i++;
    }
}
/*
 * Prints help (usage) message with cerr.
 * This is a static method.
 */
void Soduku_Parser::help_message()
{
    std::ifstream inFile("soduku_driver_usage.txt");
    std::string line;
    while (not inFile.eof()) {
        getline(inFile, line);
        std::cerr << line << std::endl;
    }
}









