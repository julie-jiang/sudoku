/* 
 * Soduku_Main.cpp
 * Implementaion of the main function for the soduku program.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* 
 * Compile with: make
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
 */
#include <iostream>
#include "Soduku_Parser.h"
#include "Soduku_Driver.h"
int main(int argc, char *argv[])
{
    try {
        // Parse input
        Soduku_Parser parser(argc, argv);

        // Take one action 
        if (parser.solve_one) {
            solve_one(parser);
        } else if (parser.solve_all) {
            solve_all(parser);
        } else if (parser.check_one) {
            check_one(parser.input_path);
        } else if (parser.check_all) {
            check_all(parser.input_path);
        } else if (parser.generate) {
            generate(parser);
        }

    } catch (const std::exception &e) {
        
        // If any exceptions are caught, print error messages and exit.
        std::cerr << e.what() << std::endl;
        Soduku_Parser::help_message();
        exit(1);
    }
}