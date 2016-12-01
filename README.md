# Soduku
A Soduku solver, checker and generator. Written entirely in c++. 
The main and most interesting functionality is solving a soduku puzzle. It can solve any provided sokudu puzzle in the form of a n^2 by n^2 grid of integers, where n is a postive integer, with the number 0 serving as a placeholder for blank grid cells. 

For example, if we run the following Soduku puzzle in this program:
```
0 0 3 0 2 0 6 0 0 
9 0 0 3 0 5 0 0 1 
0 0 1 8 0 6 4 0 0 
0 0 8 1 0 2 9 0 0                   
7 0 0 0 0 0 0 0 8 
0 0 6 7 0 8 2 0 0 
0 0 2 6 0 9 5 0 0 
8 0 0 2 0 3 0 0 9 
0 0 5 0 1 0 3 0 0 
```
Then we would get the following result printed with pretty gridlines:
```
|-----------------------| 
| 4 8 3 | 9 2 1 | 6 5 7 | 
| 9 6 7 | 3 4 5 | 8 2 1 | 
| 2 5 1 | 8 7 6 | 4 9 3 | 
|-----------------------| 
| 5 4 8 | 1 3 2 | 9 7 6 | 
| 7 2 9 | 5 6 4 | 1 3 8 | 
| 1 3 6 | 7 9 8 | 2 4 5 | 
|-----------------------| 
| 3 7 2 | 6 8 9 | 5 1 4 | 
| 8 1 4 | 2 5 3 | 7 6 9 | 
| 6 9 5 | 4 1 7 | 3 8 2 | 
|-----------------------| 
```


1. [Usage](#usage) 
2. [Design](#design)
3. [Algorithms](#algorithms)
4. [Data Structures](#data-structures)
5. [Testing](#testing)
6. [Project Deviation](#project-deviation)
7. [Acknowledgements](#acknowledgements)
8. [Time spent doing this project](#time-spent-doing-this-project)

## Usage
First, compile with `make` or `make soduku`.
### Mandatory flags
```
Usage: ./run_soduku [--solve     or -s  <filename>] \
                    [--solve-all or -sa <filelist>] \
                    [--check     or -c  <filename>] \
                    [--check-all or -ca <filelist>] \
                    [--generate  or -g  <some number>]
```
*Woah, that's a lot of options. No worries, let's go through them.*
### Solve
You can either solve one puzzle or solve a bunch of puzzle. 
To solve one puzzle, you must provide the name of the file that contains a Soduku puzzle in the following format:
```
0 6 2 3 4 0 7 5 0 
1 0 0 0 0 5 6 0 0 
5 7 0 0 0 0 0 4 0 
0 0 0 0 9 4 8 0 0 
4 0 0 0 0 0 0 0 6 
0 0 5 8 3 0 0 0 0 
0 3 0 0 0 0 0 9 1 
0 0 6 4 0 0 0 0 7 
0 5 9 0 8 3 2 6 0 
```
Suppose the puzzle name is called `my_puzzle.txt`. We can solve it using `--write` or `-w`:
```
./run_soduku --write my_puzzle.txt
```
By default, the solutions will be printed to terminal. You can change that, however, by using the optional flag `--hide` or `-h`. But wait, what are you gonna do with solutions that you can't see, hear, feel ... you can write them to a file! To do that, use the flag `--write` or `-w`, followed by the directory to write to. 

For example, suppose you want to solve the puzzle, hide the output, and write the solutions to the current directory:
```
./run_soduku --solve my_puzzle.txt --hide --write .
```
The solution file `my_puzzle_solution.txt` can be found in the current directory. 
You can also display the outputs *and* write to file, just omit the `--hide` command in the above example.
### Solve a bunch
Alternatively, you can solve a bunch of puzzles at once. To do this, you must provide the name of the file that contains the *filenames of the puzzles*. For example, if `puzzle_list.txt` contains names to a bunch of soduku puzzles:
```
./run_soduku --solve-all puzzle_list.txt --write allsolutions --hide
```
This will write the solutions to all the puzzles listed in puzzle_list.txt
to the directory `allsolutions`, provided that the directory exists. There will also be an additional file called `puzzle_list_solutions_list.txt` in `allsolutions` that lists the name of all the file generated.
### Check
You can also check the validity of solved puzzles.
```
./run_soduku --check my_puzzle_solution.txt
```
### Check a bunch
Or check a bunch of puzzles given the file that contains the filenames of these puzzles:
```
./run_soduku --check allsolutions/puzzle_list_solutions_list.txt
```
The output to terminal will indicate the validity of the puzzles checked.

### Generate
To generate Soduku puzzle, use `--generate` or `-g`:
```
./run_soduku --generate
```
This will randomly generate a 9 by 9 puzzle, which will be printed to terminal.

### Generate a bunch 
You can also feed `--generate` an optional second argument, which must be a positive integer. This will tell the program to generate that number of puzzles.

Of course, you guessed it, you can write the generated puzzle to file! Suppose you want to generate 10 puzzles, write the solved puzzles to a directory called `allpuzzles`, and hide the output:
```
./run_soduku --generate 10 -w allpuzzles -h
```
The list to the filenames of the generated puzzles will be called `puzzle_list.txt` and will be located in `allpuzzles`.

You can also generate Soduku puzzles of arbitrary size -- well, not really. This size has to be a perfect square of another integer, due to the way Soduku puzzles are constructed. To do this, use the flag `--size` or `-n` and follow up with an integer. You can specify the difficulty of the Soduku puzzle as well. Difficulty is determined by the number of indeterminate values in the puzzle. A `hard` puzzle will have approximately 80% of the values removed, a `medium` puzzle will have 50% removed, and an `easy` puzzle will only have 30% removed. The default size is 9 and difficulty is "medium". 

Put together, if we want to generate 15 puzzles 16 by 16 in size that are `hard`, hide the output and write to the directory `reallyhardpuzzles`:
```
./run_soduku -g 15 --difficulty hard --size 16 -w reallyhardpuzzles -h
```
Now go find your puzzles in `reallyhardpuzzles`!

**That's pretty cool! I'm curious to see what's happening behind the scenes though...**

So did I! You can visualize the solving and generating process for any solve or generate commands by adding the flag `--show` or `-s`. Beware: the program is forced to sleep for 0.1 seconds before each re-print so you have time to see the output. This may significantly slow the runtime. You cannot, however, use `--show` in conjunction with `--hide`. That just doesn't make much sense.

## Design
The `main` function resides in `Soduku_Main.cpp`. It first creates a `Soduku_Parser` object to parse command line arguments, then creates a `Soduku_Driver` object to invoke a driver function. Depending on the command line arguments, `Soduku_Driver` will create a `Soduku_Solver`, `Soduku_Checker`, or `Soduku_Generator` object.

`Soduku_Solver`, `Soduku_Checker` and `Soduku_Generator` are all derived classes of `Soduku`. While they do vastly different things, some of the variables and functions are shared amongst two or all of them. The `Soduku` class on its own, however, is useless.

In a nutshell:

![alt text](design.png "soduku program design")

In addition, `Soduku_Util` contains helper function that may be shared across multiple `Soduku*` files.

## Algorithms
Before we dive in to the algorithms, let's make some formal definition. 


The algorithm primarily used is a depth-first backtracking search algorithm.
### In solving a puzzle
Constraint propagation is used in conjunction with a depth-first backtracking search algorithm to find a solution or partial solution. 
## Data Structures 

1. [Set](Set/)
	
	A self-balancing AVL binary search tree designed to hold any object.

2. [Hash Table](HashTable/)
	
	A hash table that maps one object to another.



## Testing
To test my soduku solver, I will write a `SodukuGenerator.cpp` which will be able to generate soduku puzzles of arbitrary size. 
## Project Deviation

## Acknowledgements

## Time spent doing this project
Too many. But in retrospect, totally would do it again.


