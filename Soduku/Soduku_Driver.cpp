/* 
   Soduku_Driver.cpp
   Implementations of the Soduku_Driver class. Contains the solve_one, 
   solve_all, check_one, check_all and generate functions, amongst other helper 
   functions.
 
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* This class must be used in conjunction with a Soduku_Parser object. 
   An instance of this class will be created in the main function 
   (in Soduku_Main.cpp) of the run_soduku program. 
   It contains all the driver functions for the run_soduku program. */
#include <iostream>
#include <fstream>
#include <cassert>
#include "Soduku_Driver.h"
#include "Soduku_Solver.h"
#include "Soduku_Checker.h"
#include "Soduku_Generator.h"
#include "Soduku_Parser.h"
#include "Soduku_Util.h"

/* Take one action.
   Assumes that only one of the five booleans parser.solve_one, 
   parser.solve_all, parser.check_one, parser.check_all and parser.generate
   is true. */
Soduku_Driver::Soduku_Driver(const Soduku_Parser &parser)  {
         if (parser.solve_one) { solve_one(parser); }        
    else if (parser.solve_all) { solve_all(parser); }     
    else if (parser.check_one) { check_one(parser); }
    else if (parser.check_all) { check_all(parser); }
    else /*(parser.generate)*/ { generate (parser); }
}
/*****************************************************************************/
/*                             Solve functions                               */
/*****************************************************************************/

/* Solves one puzzle contained in Soduku_Parser.input_path.
   May print to terminal and may write to file.*/
void Soduku_Driver::solve_one(const Soduku_Parser &parser) {
    Soduku_Solver solver(parser.input_path);
    if (parser.print) {
        solver.print_solution();
    }
    if (parser.write) {
        solver.write_solution(parser.output_path);
    }
}
/*  Solves all soduku puzzles contained in Soduku_Parser.input_path
   May print to terminal and may write to file. Also generates
   a file that contains a list of paths to solution files, if it will write 
   solutions to files. (done in helper function solve_all_and_write).*/
void Soduku_Driver::solve_all(const Soduku_Parser &parser) {
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
/* Solves all soduku puzzles contained in Soduku_Parser.input_path and writes
   all solutions to the directory parser.output_path. Also generates
  a file that contains a list of paths to solution files. */
void Soduku_Driver::solve_all_and_write(const Soduku_Parser &parser) {
    // Open input file
    std::ifstream inFile;
    inFile.open(parser.input_path);
    if (inFile.fail()) 
        throw std::logic_error("File "+ parser.input_path + " does not exist");
    // Open the output file that contains list of paths to solution files
    std::string output_filelist = (parser.output_path + "/" + 
                                   get_raw_name(parser.input_path) +
                                   "_solutions_list.txt");
    std::ofstream outFile(output_filelist);
    if (not outFile.is_open()) {
        throw std::logic_error("ERROR: " + parser.output_path + 
                               " is not a valid directory");
    }
    std::string puzzle_name;  // Solve each puzzle 
    while (inFile >> puzzle_name) {
        Soduku_Solver solver(puzzle_name);
        if (parser.print) 
            solver.print_solution();
        solver.write_solution(parser.output_path);
        // Output the file name to outFile
        std::string filename = (parser.output_path + "/" + 
                                 get_raw_name(puzzle_name) + 
                                 "_solution.txt");
        outFile << filename << std::endl;
    }
    std::cout << "List of paths to solved puzzles can be found at: ";
    std::cout << output_filelist<< "\n";
    outFile.close();
}
/*****************************************************************************/
/*                             Check functions                               */
/*****************************************************************************/
/* Checks the validity of one soduku solution contained in the file
   parser.input_path. Results will be printed via standard cout. */
void Soduku_Driver::check_one(const Soduku_Parser &parser) {
    Soduku_Checker checker;
    if (checker.check_solution(parser.input_path)) {
        std::cout << parser.input_path << " is a solved Soduku puzzle!\n";
    } else {
        std::cout << "Uh oh ... " << parser.input_path << " is not solved :(\n";
    }
}
/* Checks the validity of all soduku solutions contained in the files
   indicated in file parser.input_path.
   Results will be printed via standard cout. */
void Soduku_Driver::check_all(const Soduku_Parser &parser) {
    // Open input file
    std::ifstream inFile;
    inFile.open(parser.input_path);
    if (inFile.fail()) {
        throw std::logic_error("File " + parser.input_path + " does not exist");
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
        std::cout << "All Soduku puzzles in " << parser.input_path
                  << " are solved!\n";
    }
}
/*****************************************************************************/
/*                            Generate functions                             */
/*****************************************************************************/

/* Generate one or many Soduku puzzle of size parser.generate_size. 
   May print to terminal and may write to file. */
void Soduku_Driver::generate(const Soduku_Parser &parser) {
    // seed time
    srand(time(NULL)); 
    // Either generate one or generate a bunch
    (parser.num_generate == 1) ? generate_one(parser) : generate_all(parser);
}

/* Generate one Soduku puzzle of size parser.generate_size.
   May print to terminal and may write to file.
   If writing to file, the file will be named puzzle.txt*/
void Soduku_Driver::generate_one(const Soduku_Parser &parser) {
    Soduku_Generator generator(parser.generate_difficulty, 
                               parser.generate_size);
    if (parser.print) {
        generator.print_puzzle();
    }
    if (parser.write) {
        generator.write_puzzle(parser.output_path);
        std::string filename = parser.output_path + "/puzzle.txt";
        std::cout << "Generated puzzles can be found at: ";
        std::cout << filename << "\n";
    }
}
/* Generate parser.num_generate puzzles of size parser.generate_size.
   May print to terminal and may write to file. 
   If writing to file, call helper function generate_all_and_write */
void Soduku_Driver::generate_all(const Soduku_Parser &parser) {
    if (parser.write) {
        generate_all_and_write(parser);
        return;
    }
    for (int i = 0; i < parser.num_generate; i++) {
        Soduku_Generator generator(parser.generate_difficulty, 
                                   parser.generate_size);
        if (parser.print) {
            generator.print_puzzle();
        }
        
    }
}
/* Generate parser.num_generate puzzles of size parser.generate_size.
   May print to terminal and may write to file. 
   If writing to file, then a file consisting of all the paths to the generated
   puzzles will be made. This file is named puzzle_list.txt */
void Soduku_Driver::generate_all_and_write(const Soduku_Parser &parser) {
    // Open the output file that contains list of paths to solution files
    std::string output_filelist = (parser.output_path + "/puzzle_list.txt");
    std::ofstream outFile(output_filelist);
    if (not outFile.is_open()) {
        throw std::logic_error("ERROR: " + parser.output_path + 
                               " is not a valid directory");
    }
    for (int i = 0; i < parser.num_generate; i++) {
        Soduku_Generator generator(parser.generate_difficulty, 
                                   parser.generate_size);
        if (parser.print) {
            generator.print_puzzle();
        }
        generator.write_puzzle(parser.output_path, int2string(i + 1));
        std::string filename = parser.output_path
                               + "/puzzle" + int2string(i + 1) + ".txt";
        outFile << filename << std::endl;
    }
    std::cout << "List of paths to generated puzzles can be found at: ";
    std::cout << output_filelist << "\n";
}






