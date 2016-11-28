/*
 * Driver for the Soduku class. Contains the main function.
 */
#include <iostream>
#include <fstream>
#include "Soduku.h"
#include "Soduku_Parser.h"
void solve_all(Soduku_Parser &);
void solve_one(Soduku_Parser &);

int main(int argc, char *argv[])
{
    try {
        // Parse input
        Soduku_Parser parser(argc, argv);

        // Either solve one puzzle or solve all puzzles
        parser.solve_one? solve_one(parser) : solve_all(parser);

    } catch (const std::exception &e) {
        // If any exceptions are caught, print error messages and exit.
        std::cerr << e.what() << std::endl;
        Soduku_Parser::help_message();
        exit(1);
    }
}

/* 
 * Solve all soduku puzzles contained in Soduku_Parser.filelist
 */
void solve_all(Soduku_Parser &parser)
{
    // Open input file
    std::ifstream inFile;
    inFile.open(parser.filelist);
    if (inFile.fail()) {
        throw std::logic_error("File " + parser.filelist + " does not exist");
    }

    // Process each puzzle 
    std::string puzzle;
    Soduku soduku;
    while (inFile >> puzzle) {
        soduku.solve(puzzle);
        if (parser.print) {
            soduku.print();
        }
        if (parser.write) {
            soduku.write(parser.directory);
        }
    }
}


/*
 * Solve one puzzle contained in Soduku_Parser.filename
 */
void solve_one(Soduku_Parser &parser)
{
    Soduku soduku;
    soduku.solve(parser.filename);
    if (parser.print) {
        soduku.print();
    }
    if (parser.write) {
        soduku.write(parser.directory);
    }
}










