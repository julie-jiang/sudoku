#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <time.h>
#include <vector>
#include "Soduku.h"

/* Test one easy puzzle just to see that this works! */
void test0()
{
    system("./soduku --solve data/puzzles/puzzle1.txt --write data/solutions --hide");
    std::string puzzle_name = "data/solutions/puzzle1_solution.txt";
    Soduku soduku;
    assert(soduku.check(puzzle_name));
    
}
/*
 * Test and validate all puzzles in data/puzzles/set1.
 * Solutions are located in data/solutions/set1.
 */
void test1()
{
    clock_t t;
    t = clock();
    system("./soduku --solve-all data/puzzles/set1/puzzle_list.txt --write data/solutions/set1 --hide");
    t = clock() - t;
    float solve_time = ((float)t)/ CLOCKS_PER_SEC;
    std::string filelist = "data/puzzles/set1/puzzle_list.txt";
    std::ifstream inFile(filelist);
    if (inFile.fail()) {
        throw std::logic_error("ERROR in Soduku_Tester: File " + filelist + " does not exist.");
    }
    int num_puzzles = 0;
    Soduku soduku;
    std::string filename;
    while (inFile >> filename) {
        std::string rawname = filename.substr(0, filename.find_last_of("."));
        rawname = rawname.substr(rawname.find_last_of("/\\") + 1);
        std::string puzzle_name = "data/solutions/set1/" + rawname + "_solution.txt";
        assert(soduku.check(puzzle_name));
        num_puzzles++;
    }
    std::cout << "Testing all Soduku puzzles in data/puzzles/set1 completed.\n";
    std::cout << "Total solving time = " << solve_time << "s. \n";
    std::cout << "On average " << solve_time / num_puzzles << "s per puzzle.\n\n";
}
/*
 * Test and validate all puzzles in data/puzzles/set2
 * Solutions are located in data/solutions/set2.
 */
void test2()
{
    clock_t t;
    t = clock();
    system("./soduku --solve-all data/puzzles/set2/puzzle_list.txt --write data/solutions/set2 --hide");
    t = clock() - t;
    float solve_time = ((float)t)/ CLOCKS_PER_SEC;
    std::string filelist = "data/puzzles/set2/puzzle_list.txt";
    std::ifstream inFile(filelist);
    if (inFile.fail()) {
        throw std::logic_error("ERROR in Soduku_Tester: File " + filelist + " does not exist.");
    }
    int num_puzzles = 0;
    Soduku soduku;
    std::string filename;
    while (inFile >> filename) {
        std::string rawname = filename.substr(0, filename.find_last_of("."));
        rawname = rawname.substr(rawname.find_last_of("/\\") + 1);
        std::string puzzle_name = "data/solutions/set2/" + rawname + "_solution.txt";
        assert(soduku.check(puzzle_name));
        num_puzzles++;
    }
    std::cout << "Testing all Soduku puzzles in data/puzzles/set2 completed.\n";
    std::cout << "Total solving time = " << solve_time << "s. \n";
    std::cout << "On average " << solve_time / num_puzzles << "s per puzzle.\n\n";
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