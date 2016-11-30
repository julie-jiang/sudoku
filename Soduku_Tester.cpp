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
/*  Compile with:
        make test
    And run:
        ./test_soduku
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <time.h>
#include <vector>
#include "Soduku/Soduku_Checker.h"
#include "Soduku/Soduku_Driver.h"

/* Helper function. Execute the given command (should be a soduku generating 
   command) and display total run time. */
void test_generate(const char *command)
{
    std::cout << "Generating soduku puzzles...\n";
    clock_t t;
    t = clock();
    system(command);
    t = clock() - t;
    double generate_time = (double) t / CLOCKS_PER_SEC;
    std::cout << "Total generating time = " << generate_time << "s \n";
}

/* Helper function. Execute the given command (should be a soduku puzzle solving 
   command) and display total run time. */
void test_solve(const char *command)
{
    std::cout << "Solving puzzles...\n";
    clock_t t;
    t = clock();
    system(command);
    t = clock() - t;
    double solve_time = (double) t / CLOCKS_PER_SEC;
    std::cout << "Total solving time = " << solve_time << "s. \n";
}

/* Helper function. Execute the given command (should be a soduku puzzle 
   checking command) and display total run time. */
void test_check(const char *command)
{
    std::cout << "Checking puzzles...\n";
    clock_t t;
    t = clock();
    system(command);
    t = clock() - t;
    double check_time = (double) t / CLOCKS_PER_SEC;
    std::cout << "Total checking time = " << check_time << "s. \n";
}
/* Test one easy puzzle just to see that this works! */
void test0()
{
  std::cout << "Beginning test 0\n";
    test_solve("./run_soduku --solve data/puzzles/set1/puzzle1.txt \
                --write data/solutions/set1 --hide");
    test_check("./run_soduku --check \
                data/solutions/set1/puzzle1_solution.txt");
    std::cout << "Finished executing test on data/puzzles/set1/puzzle1.txt\n\n";
    
}
/* Test 1
   Tests puzzles in data/puzzles/set1 by solving them and then checking their 
   solutions.
   Puzzles should preexist in data/puzzles/set1, and there should be a file 
   called puzzle_list.txt in that directory that contains the paths to all
   puzzles.
   Solutions are located in data/solutions/set1.
   All of test set 1 puzzles are taken from Project Euler 
   (https://projecteuler.net/problem=96)  */
void test1()
{
    std::cout << "Beginning test 1\n";
    system("mkdir data/solutions/set1");
    test_solve("./run_soduku --solve-all data/puzzles/set1/puzzle_list.txt \
                 --write data/solutions/set1 --hide");
    test_check("./run_soduku --check-all \
                 data/solutions/set1/puzzle_list_solutions_list.txt");

    std::cout << "Finished executing test set data/puzzles/set1.\n\n";
}

/* Test 2
   Tests puzzles in data/puzzles/set2 by solving them and then checking their 
   solutions.
   Puzzles should preexist in data/puzzles/set2, and there should be a file 
   called puzzle_list.txt in that directory that contains the paths to all
   puzzles.
   Solutions are located in data/solutions/set2.
   All of test set 2 puzzles are taken from online, but I forgot where...
   There are supposedly really hard 9 by 9 soduku puzzles.
   Running this test could take a while because of the sheer amount of puzzles
   in this set (almost 400) */
void test2()
{
    std::cout << "Beginning test 2\n";
    std::cout << "Running tests on all Soduku puzzles in ";
    std::cout << "data/puzzles/set2 ...\n";
    test_solve("./run_soduku --solve-all data/puzzles/set2/puzzle_list.txt \
                 --write data/solutions/set2 --hide");
    test_check("./run_soduku --check-all \
                 data/solutions/set2/puzzle_list_solutions_list.txt");
    
    std::cout << "Finished executing test set data/puzzles/set2.\n\n";
}

/* Test 3
   Generate 10 easy 9 by 9 Soduku puzzles, solve these puzzles, and then check
   their solutions.
   Generated puzzles will be located in data/puzzles/set3.
   Solutions will be located in data/solutions/set3. */
void test3()
{
    std::cout << "Beginning test 3\n";
    system("mkdir data/puzzles/set3");
    system("mkdir data/solutions/set3");
    test_generate("./run_soduku --generate 10 --write data/puzzles/set3 \
                   --difficulty easy --hide");
    test_solve("./run_soduku --solve-all data/puzzles/set3/puzzle_list.txt \
                --write data/solutions/set3 --hide");
    test_check("./run_soduku --check-all \
                  data/solutions/set3/puzzle_list_solutions_list.txt");
    std::cout << "Finished executing test set data/puzzles/set3.\n\n";
}

/* Test 4
   Generate 100 hard 9 by 9 Soduku puzzles, solve these puzzles, and then check
   their solutions.
   Generated puzzles will be located in data/puzzles/set4.
   Solutions will be located in data/solutions/set4. */
void test4()
{
    std::cout << "Beginning test 4\n";
    system("mkdir data/puzzles/set4");
    system("mkdir data/solutions/set4");
    test_generate("./run_soduku --generate 100 --write data/puzzles/set4 \
                   --difficulty hard --hide");
    test_solve("./run_soduku --solve-all data/puzzles/set4/puzzle_list.txt \
                --write data/solutions/set4 --hide");
    test_check("./run_soduku --check-all \
                 data/solutions/set4/puzzle_list_solutions_list.txt");
    std::cout << "Finished executing test set data/puzzles/set4.\n\n";
}

/* Test 5
   Generate 50 medium 16 by 16 Soduku puzzles, solve these puzzles, and then 
   check their solutions.
   Generated puzzles will be located in data/puzzles/set4.
   Solutions will be located in data/solutions/set4. */
void test5()
{
    std::cout << "Beginning test 5\n";
    system("mkdir data/puzzles/set5");
    system("mkdir data/solutions/set5");
    test_generate("./run_soduku --generate 50 --write data/puzzles/set5 \
                   --size 16 --hide");
    test_solve("./run_soduku --solve-all data/puzzles/set4/puzzle_list.txt \
                --write data/solutions/set5 --hide");
    test_check("./run_soduku --check-all \
                data/solutions/set5/puzzle_list_solutions_list.txt");
    std::cout << "Finished executing test set data/puzzles/set5.\n\n";
}

/* Test 6
   Generate 5 medium 25 by 25 Soduku puzzles, solve these puzzles, and then 
   check their solutions.
   Generated puzzles will be located in data/puzzles/set6.
   Solutions will be located in data/solutions/set6. 
   This test could take a while. */
void test6()
{
    std::cout << "Beginning test 6\n";
    system("mkdir data/puzzles/set6");
    system("mkdir data/solutions/set6");
    test_generate("./run_soduku --generate 5 --write data/puzzles/set6 \
                   --size 25 --hide");
    test_solve("./run_soduku --solve-all data/puzzles/set6/puzzle_list.txt \
                --write data/solutions/set6 --hide");
    test_check("././run_soduku --check-all \
                data/solutions/set6/puzzle_list_solutions_list.txt");
    std::cout << "Finished executing test set data/puzzles/set6.\n\n";
}
/* Test 7
   Generate 10 easy 36 by 36 Soduku puzzles, solve these puzzles, and then 
   check their solutions.
   Generated puzzles will be located in data/puzzles/set7.
   Solutions will be located in data/solutions/set7. 
   This test could take a while. */
void test7()
{
    std::cout << "Beginning test 7\n";
    system("mkdir data/puzzles/set7");
    system("mkdir data/solutions/set7");
    test_generate("./run_soduku --generate 5 --write data/puzzles/set7 \
                   --size 36 --hide");
    test_solve("./run_soduku --solve-all data/puzzles/set7/puzzle_list.txt \
                --write data/solutions/set7 --hide");
    test_check("./run_soduku --check-all \
                 data/solutions/set7/puzzle_list_solutions_list.txt");
    std::cout << "Finished executing test set data/puzzles/set7.\n\n";
}
int main()
{
    std::cout << "Running system tests for Soduku\n";
    test0();
    test1();
    //test2();
    test3();
    test4();
    test5();
    //test6();
    //test7();
    std::cout << "All tests completed! \n";
    
}