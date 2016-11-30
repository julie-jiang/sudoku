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
#include "Soduku_Parser.h"
#include "Soduku_Util.h"
Soduku_Parser::Soduku_Parser(int argc, char *argv [])
{
    init_default_settings();

    if (argc < 2) { // Must have at least 2 arguments
        throw std::logic_error("ERROR: missing mandatory arguments");
    }

    parse_first_flag(std::string(argv[1]));
    if (not generate) {
        if (argc < 3) {
            throw std::logic_error("ERROR: missing mandatory arguments");
        }
        input_path = std::string(argv[2]);
        parse_optional_flags(3, argc, argv);
    } else if (argc > 2) {
        if (std::string(argv[2]).substr(0, 1) == "-") {
            parse_optional_flags(2, argc, argv);
        } else {
            num_generate = string2int(std::string(argv[2]));
            std::cout << num_generate << "\n";
            parse_optional_flags(3, argc, argv);
        }
    }
}
// Initialize default settings
void Soduku_Parser::init_default_settings()
{
    solve_one = solve_all = check_one = check_all = write = generate = false;
    print = true;  
    generate_difficulty = "medium";
    num_generate = 1;
    generate_size = 9;
}
/*
 * Parse the first argument and stores the input_path.
 */
void Soduku_Parser::parse_first_flag(std::string arg)
{
    if (arg == "--solve" or arg == "-s") {
        solve_one = true;
    } else if (arg == "--solve-all" or arg == "-sa") {
        solve_all = true;
    } else if (arg == "--check" or arg == "-c") {
        check_one = true;
    } else if (arg == "--check-all" or arg == "-ca") {
        check_all = true;
    } else if (arg == "--generate" or arg == "-g") {
        generate = true;
    } else if (arg == "--help" or arg == "-h") {
        print_usage();
        exit(0);
    } else {
        throw std::logic_error("ERROR: Invalid mandatory argument");
    }
}
/*
 * Parses any additional optional arguments
 */
void Soduku_Parser::parse_optional_flags(int i, int argc, char *argv[])
{
    while (i < argc) {
        std::string arg = argv[i];
        if ((arg == "--write" or arg == "-w") and i + 1 < argc) {
            write = true;
            output_path = argv[i + 1];
            i++;
        } else if (arg == "--hide" or arg == "-h") {
            print = false;
        } else if (generate and (arg == "--difficulty" or arg == "-d") 
                   and i + 1 < argc) {
            generate_difficulty = argv[i + 1];
            i++;
        } else if (generate and (arg == "--size" or arg == "-n") 
                   and i + 1 < argc) {
            generate_size = string2int(argv[i + 1]);
            i++;
        } else {
            throw std::logic_error("ERROR: Unknown command line argument " + 
                                    arg);
        }
        i++;
    }
}
void Soduku_Parser::print_usage()
{
    std::ifstream inFile("soduku_driver_usage.txt");
    std::string line;
    while (not inFile.eof()) {
        getline(inFile, line);
        std::cout << line << std::endl;
    }
}
/*
 * Prints a quick blurb of usage with cerr.
 * This is a static method.
 */
void Soduku_Parser::help_message()
{
    std::cerr << "Usage: ./soduku [--solve     or -s  <filename>] or \n";
    std::cerr << "                [--solve-all or -sa <filelist>] or \n";
    std::cerr << "                [--check     or -c  <filename>] or \n";
    std::cerr << "                [--check-all or -ca <filelist>] or \n";
    std::cerr << "                [--generate  or -g  <some number>] \n";
    std::cerr << "For more usage information: --help or -h\n";
}









