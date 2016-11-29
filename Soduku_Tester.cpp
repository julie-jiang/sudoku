/* 
 * Soduku_Tester.cpp
 * System tests for the Soduku_Solver class.
 *
 * By:   Julie Jiang
 * UTLN: yjiang06
 * Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* 
 * Compile with:
 *      make test
 * And run:
 *      ./test_soduku
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <time.h>
#include <vector>
#include "Soduku_Checker.h"
#include "Soduku_Driver.h"

/* Test one easy puzzle just to see that this works! */
void test0()
{
    system("./soduku --solve data/puzzles/puzzle1.txt \
            --write data/solutions --hide");
    std::string puzzle_name = "data/solutions/puzzle1_solution.txt";
    Soduku_Checker soduku;
    assert(soduku.check(puzzle_name));
    
}
/*
 * Test and validate all puzzles in data/puzzles/set1.
 * Solutions are located in data/solutions/set1.
 * All puzzles are taken from https://projecteuler.net/problem=96 
 */
void test1()
{
    std::cout << "Running tests on all Soduku puzzles in "
    std::cout << "data/puzzles/set1 ...\n";
    clock_t t;
    t = clock();
    system("./soduku --solve-all data/puzzles/set1/puzzle_list.txt \
            --write data/solutions/set1 --hide");
    t = clock() - t;
    float solve_time = ((float)t)/ CLOCKS_PER_SEC;

    std::cout << "Total solving time  = " << solve_time << "s. \n";

    t = clock();
    assert(check_all("data/solutions/set1/puzzle_list_solutions_list.txt"));
    t = clock() - t;
    float check_time = ((float)t)/ CLOCKS_PER_SEC;
    std::cout << "Total checking time = " << check_time << "s. \n";
    std::cout << "Finished executing test set data/puzzles/set1.\n\n";
    
    
}
/*
 * Test and validate all puzzles in data/puzzles/set2
 * Solutions are located in data/solutions/set2.
 * All puzzles are taken from online ... but I forgot where.
 */
void test2()
{
    std::cout << "Running tests on all Soduku puzzles in "
    std::cout << "data/puzzles/set2 ...\n";
    clock_t t;
    t = clock();
    system("./soduku --solve-all data/puzzles/set2/puzzle_list.txt \
            --write data/solutions/set2 --hide");
    t = clock() - t;
    float solve_time = ((float)t)/ CLOCKS_PER_SEC;
    std::cout << "Total solving time  = " << solve_time << "s. \n";

    t = clock();
    assert(check_all("data/solutions/set2/puzzle_list_solutions_list.txt"));
    t = clock() - t;
    float check_time = ((float)t)/ CLOCKS_PER_SEC;

    std::cout << "Total checking time = " << check_time << "s. \n";
    std::cout << "Finished executing test set data/puzzles/set2.\n\n";
    
    
}
int main()
{
    std::cout << "Running system tests for Soduku\n";
    test0();
    test1();
    test2();
    std::cout << "All tests completed! \n";
    
}