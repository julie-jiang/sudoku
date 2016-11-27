#include <iostream>
#include <fstream>
#include "Soduku.h"

const int size = 9;
void solve_all(std::string filelist)
{
    std::ifstream inFile;
    inFile.open(filelist);
    if (inFile.fail()) {
        throw std::logic_error("File does not exist");
    }
    std::string puzzle;
    while (inFile >> puzzle)
        Soduku soduku(puzzle, size);

}
int main(int argc, char *argv[])
{
    try {
        if (argc < 2) {
            throw std::logic_error("Incorrect number of arguments");
        }
        solve_all(std::string(argv[1]));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: soduku filename \n";
        exit(1);
    }
    
}