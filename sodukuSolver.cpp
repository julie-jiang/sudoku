#include <iostream>
#include <fstream>
#include "Soduku.h"

void solve_all(std::string filelist)
{
    std::ifstream inFile;
    inFile.open(filelist);
    if (inFile.fail()) {
        throw std::logic_error("File does not exist");
    }
    std::string puzzle;
    while (inFile >> puzzle) {
        Soduku soduku(puzzle);
        soduku.print();
    }
}
void help_message()
{
    std::cerr << "Usage: ./soduku [--solve or -s <filename>]\n"
                 "                [--solve-all   <filelist>]\n"
                 "                [--write or -w <directory>]\n"
                 "\n"
                 "solve      Provide path to a Soduku puzzle\n"
                 "solve-all  Provide path to a list of paths to Soduku puzzles\n"
                 "write      Specify directory to write solution files to\n";

}
int main(int argc, char *argv[])
{
    try {
        if (argc < 2) {
            throw std::logic_error("ERROR: Incorrect number of arguments");
        }
        solve_all(std::string(argv[1]));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        help_message();
        exit(1);
    }
    
}