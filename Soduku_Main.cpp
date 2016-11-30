/* 
 * Soduku_Main.cpp
 * Implementaion of the main function for the soduku program. Functionalities
 * include solving soduku puzzles, checking soduku puzzles and generating
 * soduku puzzles.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/*  Compile with: make
Usage: ./soduku [--solve     or -s  <filename>] \
                [--solve-all or -sa <filelist>] \
                [--check     or -c  <filename>] \
                [--check-all or -ca <filelist>] \
                [--generate  or -g  <some number>]

Mandatory flags (must provide one and only one of the following FIRST):
--solve      or -s  <filename>
                    Solve a single Soduku puzzle. 
                    Provide path to a unsolved Soduku puzzle.
--solve-all  or -sa <filelist>
                    Solve all Soduku puzzles. 
                    Provide path to a list of paths to unsolved Soduku puzzles
--check      or -c  <filename>
                    Check the validity of a single Soduku puzzle. 
                    Provided path to a unsolved Soduku puzzle.
--check-all  or -ca <filelist>
                    Check the validity of all solved Soduku puzzles. 
                    Provide path to a list of paths to solved Soduku puzzles.
--generate   or -g  <some number>
                    Generate one or many Soduku puzzle, depending on the next 
                    integer argument provided. If no subsequent argument is 
                    provided or if the next argument is a flag, then the number 
                    of puzzles to be generated will default to 1.
--help       or -h  See more usage information.

Optional flags for --solve, --solve-all or --generate:
--write      or -w   <directory>
                    Write puzzle to the specified directory as a .txt file.
--hide       or -h  Disable the default setting that print puzzle to console.

More optional flags for --generate:
--difficulty or -d  <level>
                    Generate either "hard", "medium" or "easy" soduku puzzles.
                    Default setting is "medium".
--size       or -n  <some number>
                    Generate a puzzle based on the given size. E.g. if the 
                    argument is 16, then a 16 by 16 Soduku puzzle will be 
                    generated. This number must be a perfect square.
                    Default setting is 9.
*/
#include <iostream>
#include "Soduku/Soduku_Parser.h"
#include "Soduku/Soduku_Driver.h"
int main(int argc, char *argv[])
{
    try {
        Soduku_Parser parser(argc, argv);   // Parse input. See Soduku_Parser
        Soduku_Driver driver(parser);       // Take action. See Soduku_Driver
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;  // If any exceptions are caught,
        Soduku_Parser::help_message();       // print error messages and exit.
        exit(1);
    }
}





