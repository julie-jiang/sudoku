# Soduku Solver
This is a Soduku solver. It can solve any provided sokudu puzzle in the form of a n^2 by n^2 grid of integers, where n is a postive integer, with the number 0 serving as a placeholder for blank grid cells. Below is an example Soduku of size 3^2 by 3^2 = 9 by 9 input on the left, and its solution output on the right:
```
003020600        483921657 
900305001        967345821 
001806400        251876493 
008102900        548132976 
700000008        729564138 
006708200        136798245 
002609500        372689514 
800203009        814254769 
005010300        695417382
```
## Design
The `main` function resides in `sodukuSolver.cpp`, in which an instance of the class `Soduku` will be created. All of the search functions used to find a solution will be implemented within `Soduku`. The `Soduku` class also utilizes several data structures, including but not limited to AVL trees, hash tables, queues, stacks, priority queues, and maps (this will be completely replaced by hash tables in the final version).

The variables in `Soduku`, which are the individual grid cells, are implemented as instances of the `Coord` object, short for coordinates. It simply holds two integers x and y that specify where in the grid this object refers to.

## Usage
Compile with:
```
make
```
And run:
```
./sodukuit <path to list of soduku puzzles>
```

For example: 
```
./sodukuit puzzle/puzzle_list.txt
```

## Data Structures

1. [Set](Set/)
	
	A self-balancing AVL binary search tree designed to hold any object.

2. [Hash Map](HashMap/)
	
	A hash table that maps one object to another.

3. Priority Queue
	
	A PQ that holds coordinate objects `Coord`, prioritized by the number of values in their domains.


## Testing
To test my soduku solver, I will write a `SodukuGenerator.cpp` which will be able to generate soduku puzzles of arbitrary size. 

## Read more
Please see [my spec](Julie Jiang Comp 15 Final Project Specs.pdf) for formal definitions and algorithms rendered in beautiful LaTeX. However, some outlines of the design in the spec might be outdated, since, as you may know, plans can change.