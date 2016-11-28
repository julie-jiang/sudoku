#include <iostream>
#include <sstream>
#include <time.h>
#include "Soduku_Checker.h"
void run_test()
{
	system("./soduku --solve-all puzzles/puzzle_list.txt --write solutions --hide");
	std::string filelist = "solutions/puzzle_list_solutions_list.txt";
	std::ifstream inFile;
	inFile.open(filelist);
	if (inFile.fail()) {
        throw std::logic_error("File " + filelist + " does not exist");
    }
    Soduku_Checker soduku_checker();
    while (inFile >> puzzle) {
    	assert(soduku_checker(puzzle));
    }
}
int main()
{
	try {
		std::cout << "Running system tests for Soduku\n";
		clock_t t;
		t = clock();
		run_test();
		t = clock() - t;
		std::cout << "Finished executing in test set in " 
		          << ((float)t)/ CLOCKS_PER_SEC 
		          << " seconds \n";
	}
}