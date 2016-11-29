# Soduku Solver
This is a Soduku solver. It can solve any provided sokudu puzzle in the form of a n^2 by n^2 grid of integers, where n is a postive integer, with the number 0 serving as a placeholder for blank grid cells. Below is an example Soduku of size 3^2 by 3^2 = 9 by 9.

Input:

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
Standard cout:

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
Write to file:

```
4 8 3 9 2 1 6 5 7 
9 6 7 3 4 5 8 2 1 
2 5 1 8 7 6 4 9 3 
5 4 8 1 3 2 9 7 6 
7 2 9 5 6 4 1 3 8 
1 3 6 7 9 8 2 4 5 
3 7 2 6 8 9 5 1 4 
8 1 4 2 5 3 7 6 9 
6 9 5 4 1 7 3 8 2 
```

## Design
The `main` function resides in `Soduku_Driver.cpp`, in which an instance or instances of the class `Soduku` will be created. All of the puzzle solving functions is implemented within `Soduku`. The `Soduku` class also utilizes several data structures, including AVL trees, hash maps, queues, stacks, and vectors.

The variables in `Soduku`, which are the individual grid cells, are implemented as instances of the `Coord` object (see [Coord](Coord/)), short for coordinates. It simply holds two integers x and y that specify where in the grid this object refers to.

## Usage
### Compilation
```
make
```
### Options 
```
./soduku [--solve or -s <filename>] \
         [--solve-all or -a <filelist>]\
         [--write or -w <directory>] \
         [--hide or -h]
```

1. `solve`: Provide path to a Soduku puzzle
2. `solve-all`: Provide path to a list of paths to Soduku puzzles
3. `write`: Write solution files to the specified directory
4. `hide`: Disable the default setting that print solutions to console

Client must provide one (and only one) of `solve` or `solve-all`

### Examples
To solve a single puzzle called `puzzle1.txt` in the directory `puzzle`:
```
./soduku -solve puzzle/puzzle1.txt
```

To solve all puzzles whose paths are contained in `data/puzzles/set1/puzzle_list.txt`, write solutons to the directory `data/solutions/set1`, and hide output to terminal:
```
./soduku --solve-all data/puzzles/set1/puzzle_list.txt --hide --write data/solutions/set1
```


## Data Structures that I implemented

1. [Set](Set/)
	
	A self-balancing AVL binary search tree designed to hold any object.

2. [Hash Map](HashMap/)
	
	A hash table that maps one object to another.

## Testing
To test my soduku solver, I will write a `SodukuGenerator.cpp` which will be able to generate soduku puzzles of arbitrary size. 
