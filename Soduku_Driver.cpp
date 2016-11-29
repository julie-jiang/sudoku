/*
 * Driver for the Soduku class. Contains the main function.
 */
#include <iostream>
#include <fstream>
#include "Soduku.h"
#include "Soduku_Parser.h"

typedef void (*funcPtr) (Soduku_Parser &);
void solve_all(Soduku_Parser &);
void solve_one(Soduku_Parser &);
void check_one(Soduku_Parser &);
void check_all(Soduku_Parser &);
funcPtr get_function(Soduku_Parser &);


int main(int argc, char *argv[])
{
    try {
        // Parse input
        Soduku_Parser parser(argc, argv);
        funcPtr soduku_todo = get_function(parser);
        soduku_todo(parser);

    } catch (const std::exception &e) {
        // If any exceptions are caught, print error messages and exit.
        std::cerr << e.what() << std::endl;
        Soduku_Parser::help_message();
        exit(1);
    }
}
funcPtr get_function(Soduku_Parser &parser)
{
    if (parser.solve_one) 
        return solve_one;
    else if (parser.solve_all)
        return solve_all;
    else if (parser.check_one)
        return check_one;
    else
        return check_all;

}
/* 
 * Solve all soduku puzzles contained in Soduku_Parser.input_path
 */
void solve_all(Soduku_Parser &parser)
{
    // Open input file
    std::ifstream inFile;
    inFile.open(parser.input_path);
    if (inFile.fail()) {
        throw std::logic_error("File " + parser.input_path + " does not exist");
    }

    // Solve each puzzle 
    std::string puzzle_name;
    Soduku soduku;
    while (inFile >> puzzle_name) {
        soduku.solve(puzzle_name);
        if (parser.print) {
            soduku.print();
        }
        if (parser.write) {
            soduku.write(parser.output_path);
        }
    }
}


/*
 * Solve one puzzle contained in Soduku_Parser.input_path
 */
void solve_one(Soduku_Parser &parser)
{
    Soduku soduku;
    soduku.solve(parser.input_path);
    if (parser.print) {
        soduku.print();
    }
    if (parser.write) {
        soduku.write(parser.output_path);
    }
}

void check_one(Soduku_Parser &parser)
{
    Soduku soduku;
    if (soduku.check(parser.input_path)) {
        std::cout << parser.input_path << " is a solved Soduku puzzle!\n";
    } else {
        std::cout << "Uh oh ... " << parser.input_path << " is not solved :(\n";
    }
}

void check_all(Soduku_Parser &parser)
{
    // Open input file
    std::ifstream inFile;
    inFile.open(parser.input_path);
    if (inFile.fail()) {
        throw std::logic_error("File " + parser.input_path + " does not exist");
    }
    bool all_pass = true;
    // Solve each puzzle 
    std::string puzzle_name;
    Soduku soduku;
    while (inFile >> puzzle_name) {
        if (not soduku.check(puzzle_name)) {
            std::cout << "Uh oh ... " << puzzle_name << " is not solved :(\n";
            all_pass = false;
        }
    }
    if (all_pass) {
        std::cout << "All Soduku puzzles in " << parser.input_path 
                  << " are solved!\n";
    }

}









