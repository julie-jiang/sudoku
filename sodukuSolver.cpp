#include <iostream>
#include "Sodukupp.h"

const int size = 9;
int main(int argc, char *argv[])
{
    try {
        if (argc < 2) {
            throw std::logic_error("Incorrect number of arguments");
        }
        Soduku soduku(std::string(argv[1]), size);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: soduku filename \n";
        exit(1);
    }
    
}