/* 
 * Soduku_Driver.cpp
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
#include <iostream>
#include <fstream>
#include "Soduku_Driver.h"
#include "Soduku_Solver.h"
#include "Soduku_Checker.h"
#include "Soduku_Generator.h"
#include "Soduku_Parser.h"
#include "Soduku_Util.h"

/*
 * Solves one puzzle contained in Soduku_Parser.input_path.
 * May print to terminal and may write to file.
 */
void solve_one(Soduku_Parser &parser)
{
    Soduku_Solver solver(parser.input_path);
    if (parser.print) {
        solver.print_solution();
    }
    if (parser.write) {
        solver.write_solution(parser.output_path);
    }
}
/* 
 * Solves all soduku puzzles contained in Soduku_Parser.input_path
 * May print to terminal and may write to file. Also generates
 * a file that contains a list of paths to solution files, if it will write 
 * solutions to files. (done in helper function solve_all_and_write).
 */
void solve_all(Soduku_Parser &parser)
{
    // If requires writing to file
    if (parser.write) {
        solve_all_and_write(parser);
        return;
    }
    // Open input file
    std::ifstream inFile;
    inFile.open(parser.input_path);
    if (inFile.fail()) {
        throw std::logic_error("File " + parser.input_path + " does not exist");
    }
    // Solve each puzzle 
    std::string puzzle_name;
    while (inFile >> puzzle_name) {
        Soduku_Solver solver(puzzle_name);
        if (parser.print) {
            solver.print_solution();
        }
    }
}
/*
 * Solves all soduku puzzles contained in Soduku_Parser.input_path and writes
 * all solutions to the directory parser.output_path. Also generates
 * a file that contains a list of paths to solution files.
 */
void solve_all_and_write(Soduku_Parser &parser)
{
    // Open input file
    std::ifstream inFile;
    inFile.open(parser.input_path);
    if (inFile.fail()) {
        throw std::logic_error("File "+ parser.input_path + " does not exist");
    }
    // Open the output file that contains list of paths to solution files
    std::string output_filelist = (parser.output_path + "/" + 
                                   get_raw_name(parser.input_path) +
                                   "_solutions_list.txt");
    std::ofstream outFile(output_filelist);
    if (not outFile.is_open()) {
        throw std::logic_error("ERROR: " + parser.output_path + 
                               " is not a valid directory");
    }
    // Solve each puzzle 
    std::string puzzle_name;
    while (inFile >> puzzle_name) {
        Soduku_Solver solver(puzzle_name);
        if (parser.print) {
            solver.print_solution();
        }
        solver.write_solution(parser.output_path);
        // Output the file name to outFile
        std::string file_name = (parser.output_path + "/" + 
                                 get_raw_name(puzzle_name) + 
                                 "_solution.txt");
        outFile << file_name << std::endl;
        
    }
    std::cout << "List of paths to solved puzzle can be found at: ";
    std::cout << output_filelist<< "\n";
    outFile.close();

}

/*
 * Checks the validity of one soduku solution contained in the input_file.
 * Returns true if it is solved.
 */
bool check_one(std::string input_file)
{
    Soduku_Checker checker;
    if (checker.check_solution(input_file)) {
        std::cout << input_file << " is a solved Soduku puzzle!\n";
        return true;
    } else {
        std::cout << "Uh oh ... " << input_file << " is not solved :(\n";
        return false;
    }
}
/*
 * Checks the validity of all soduku solutions contained in the files
 * indicated in the input_file.
 * Returns true if all of them are solved.
 */
bool check_all(std::string input_file)
{
    // Open input file
    std::ifstream inFile;
    inFile.open(input_file);
    if (inFile.fail()) {
        throw std::logic_error("File " + input_file + " does not exist");
    }
    bool all_pass = true;
    // Solve each puzzle 
    std::string puzzle_name;
    while (inFile >> puzzle_name) {
        Soduku_Checker checker;
        if (not checker.check_solution(puzzle_name)) {
            std::cout << "Uh oh ... " << puzzle_name << " is not solved :(\n";
            all_pass = false;
        }
    }
    if (all_pass) {
        std::cout << "All Soduku puzzles in " << input_file
                  << " are solved!\n";
        return true;
    }
    return false;

}


void generate(Soduku_Parser &parser)
{
    for (int i = 0; i < parser.num_generate; i++) {
        Soduku_Generator generator(parser.generate_difficulty, 
                                   parser.generate_size);
        if (parser.print) {
            generator.print_puzzle();
        }
        if (parser.write) {
            generator.write_puzzle(parser.output_path, i + 1);
        }
        std::string filename = parser.output_path
                               + "/puzzle" + int2string(i) + ".txt";
        std::cout << "Generated puzzle can be found at: " << filename << "\n";
    }
}






