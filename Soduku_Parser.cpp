#include <iostream>
#include <fstream>
#include "Soduku_Parser.h"
Soduku_Parser::Soduku_Parser(int argc, char *argv [])
{
    solve_one = solve_all = check_one = check_all = write = false;
    print = true;
    if (argc < 3) {
        throw std::logic_error("ERROR: missing mandatory argument");
    }
    parse_first_argument(std::string(argv[1]));
    input_path = std::string(argv[2]);
    parse_optional_arguments(argc, argv);
}
void Soduku_Parser::parse_first_argument(std::string arg)
{
    if (arg == "--solve" or arg == "-s") {
        solve_one = true;
    } else if (arg == "--solve-all" or arg == "-sa") {
        solve_all = true;
    } else if (arg == "--check" or arg == "-c") {
        check_one = true;
    } else if (arg == "--check-all" or arg == "-ca") {
        check_all = true;
    } else {
        throw std::logic_error("ERROR: Invalid mandatory argument");
    }
}
void Soduku_Parser::parse_optional_arguments(int argc, char *argv[])
{
    int i = 3;
    while (i < argc) {
        std::string arg = argv[i];
        if ((arg == "--write" or arg == "-w") and i + 1 < argc) {
            write = true;
            output_path = argv[i + 1];
            i++;
        } else if (arg == "--hide" or arg == "-h") {
            print = false;
        } else {
            throw std::logic_error("ERROR: Unknown command line argument " + 
                                    arg);
        }
        i++;
    }

}
void Soduku_Parser::help_message()
{
    std::ifstream inFile("soduku_driver_usage.txt");
    std::string line;
    while (not inFile.eof()) {
        getline(inFile, line);
        std::cerr << line << std::endl;
    }
}









