#include <iostream>
#include "Soduku_Parser.h"
Soduku_Parser::Soduku_Parser(int argc, char *argv [])
{
    int i = 1;
    solve_one = solve_all = write = false;
    print = true;
    while (i < argc) {
        if (not solve_one and arg_solve(argv[i]) and i + 1 < argc) {
            filename = std::string(argv[i + 1]);
            i++;
            solve_one = true;
        } else if ((not solve_all) and arg_solve_all(argv[i]) and i + 1 < argc) {
            filelist = std::string(argv[i + 1]);
            solve_all = true;
            i++;
        } else if ((not write) and arg_write(argv[i]) and i + 1 < argc) {
            directory = std::string(argv[i + 1]);
            write = true;
            i++;
        } else if (arg_hide(argv[i])) {
            print = false; 
        } else {
            throw std::logic_error("ERROR: Invalid command line arguments");
        }
        i++;
    }
    if (not solve_one != solve_all) {
        throw std::logic_error("ERROR: either solve one or solve all!");
    }
}
bool Soduku_Parser::arg_solve(std::string arg)
{  
    return (arg == "--solve" or arg == "-s");
}
bool Soduku_Parser::arg_solve_all(std::string arg)
{
    return (arg == "--solve-all" or arg == "-a");
}
bool Soduku_Parser::arg_write(std::string arg)
{
    return (arg == "--write" or arg == "-w");
}
bool Soduku_Parser::arg_hide(std::string arg)
{
    return (arg == "--hide" or arg == "-h");
}
void Soduku_Parser::help_message()
{
    std::cerr << "Usage: ./soduku [--solve     or -s <filename>] \\ \n"
                 "                [--solve-all or -a <filelist>] \\ \n"
                 "                [--write     or -w <directory>] \\ \n"
                 "                [--hide      or -h]\n"    
                 "\n"
                 "solve      Provide path to a Soduku puzzle\n"
                 "solve-all  Provide path to a list of paths to Soduku"
                             "puzzles\n"
                 "write      Write solution files to the specified directory\n"
                 "hide       Disable the default setting that print solutions "
                             "to console\n"
                 "Note: must provide one (and only one) of 'solve' or "
                 "'solve-all'\n";
}









