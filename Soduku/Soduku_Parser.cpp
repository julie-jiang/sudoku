/* 
 * Soduku_Parser.cpp
 * Implementaion of the class Soduku_Parser.cpp.
 * Parses command line arguments for the soduku program.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */

#include <iostream>
#include <fstream>
#include "Soduku_Parser.h"
#include "Soduku_Util.h"
/* Parameterized constructor. Takes in command line arguments */
Soduku_Parser::Soduku_Parser(int argc, char *argv []) {
    init_default_settings();

    if (argc < 2) {  // Must have at least 2 arguments
        throw std::logic_error("ERROR: missing mandatory arguments");
    }

    parse_first_flag(std::string(argv[1]));
    if (not generate) {  // Must be a subsequent argument that specify an
        if (argc < 3) {  // input path
            throw std::logic_error("ERROR: missing mandatory arguments");
        }
        input_path = std::string(argv[2]);
        parse_optional_flags(3, argc, argv);

    } else if (argc > 2) {  // If generate
        // If next argument is a flag
        if (std::string(argv[2]).substr(0, 1) == "-") { 
            parse_optional_flags(2, argc, argv);
        // Else next argument specifies the number of puzzles to generate
        } else {
            num_generate = string2int(std::string(argv[2]));
            if (num_generate <= 0) {
                throw std::logic_error(
                    "ERROR: please provide positive integer");
            }
            parse_optional_flags(3, argc, argv);
        }
    }
    if (not print and show_process) { // cannot both hide and show_process
        throw std::logic_error(
            "ERROR: cannot hide and show process at the same time");
    }
}
/* Initialize default settings */
void Soduku_Parser::init_default_settings() {
    solve_one = solve_all = check_one = check_all = generate = false;
    write = show_process = false;
    print = true;  
    generate_difficulty = "medium";
    num_generate = 1;
    generate_size = 9;
}
/* Parse the first argument and stores the input_path. */
void Soduku_Parser::parse_first_flag(std::string arg) {
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
    } else if (arg == "--help" or arg == "-h") { // Terminate and print usage
        print_usage();
        exit(0);
    } else {
        throw std::logic_error("ERROR: Invalid mandatory argument");
    }
}
/* Parses any additional optional arguments */
void Soduku_Parser::parse_optional_flags(int i, int argc, char *argv[]) {
    while (i < argc) {
        std::string arg = argv[i];
        if ((arg == "--write" or arg == "-w") and i + 1 < argc) {
            write = true;
            output_path = argv[i + 1];
            i++;
        } else if (arg == "--hide" or arg == "-h") {
            print = false;
        } else if (arg == "--show" or arg == "-sp") {
            show_process = true;
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
/* Prints the full doc on usage of the program. */
void Soduku_Parser::print_usage() {
    std::ifstream inFile("soduku_driver_usage.txt");
    std::string line;
    while (not inFile.eof()) {
        getline(inFile, line);
        std::cout << line << std::endl;
    }
}
/* Prints a quick blurb of usage with cerr.
   This is a static method. */
void Soduku_Parser::help_message() {
    std::cerr << "Usage: ./soduku [--solve     | s  <filename>] or \n";
    std::cerr << "                [--solve-all | sa <filelist>] or \n";
    std::cerr << "                [--check     | c  <filename>] or \n";
    std::cerr << "                [--check-all | ca <filelist>] or \n";
    std::cerr << "                [--generate  | g  <some number>] \n";
    std::cerr << "For more usage information and optional arguments: ";
    std::cerr << "--help or -h\n";
}









