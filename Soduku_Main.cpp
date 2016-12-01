/* 
   Soduku_Main.cpp
   Implementaion of the main function for the soduku program. Functionalities
   include solving soduku puzzles, checking soduku puzzles and generating
   soduku puzzles.
  
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/*  Compile with: make
    Usage: ./soduku [--solve     or -s  <filename>] \
                    [--solve-all or -sa <filelist>] \
                    [--check     or -c  <filename>] \
                    [--check-all or -ca <filelist>] \
                    [--generate  or -g  <some number>]
    For more usage information and optional arguments: --help or -h or see README
*/
#include <iostream>
#include "Soduku/Soduku_Parser.h"
#include "Soduku/Soduku_Driver.h"
int main(int argc, char *argv[]) {
    try {
        Soduku_Parser parser(argc, argv);   // Parse input. See Soduku_Parser
        Soduku_Driver driver(parser);       // Take action. See Soduku_Driver
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;  // If any exceptions are caught,
        Soduku_Parser::help_message();       // print error messages and exit.
        exit(1);
    }
}





