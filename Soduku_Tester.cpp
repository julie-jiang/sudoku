#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <time.h>
#include "Soduku.h"
/* Test one puzzle! */
void test0()
{
	system("./soduku --solve puzzles/puzzle1.txt --write solutions --hide");
	std::string puzzle_name = "solutions/puzzle1_solution.txt";
	Soduku soduku;
 	assert(soduku.check(puzzle_name));
	
}
void test1()
{
	system("./soduku --solve-all puzzles/puzzle_list.txt --write solutions --hide");
	std::string filelist = "puzzles/puzzle_list.txt";
	std::ifstream inFile(filelist);
	if (inFile.fail()) {
        throw std::logic_error("ERROR: File " + filelist + " does not exist.");
    }
    Soduku soduku;
    std::string filename;
    while (inFile >> filename) {
    	std::string rawname = filename.substr(0, filename.find_last_of("."));
    	rawname = rawname.substr(rawname.find_last_of("/\\") + 1);
    	std::string puzzle_name = "solutions/" + rawname + "_solution.txt";
    	assert(soduku.check(puzzle_name));
    }

}
int main()
{
	std::cout << "Running system tests for Soduku\n";
	clock_t t;
	t = clock();
	test1();
	test2();
	t = clock() - t;
	std::cout << "Finished executing test set in " 
		      << ((float)t)/ CLOCKS_PER_SEC 
		      << " seconds \n";
	
}