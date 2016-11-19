# Soduku Solver
This is a Soduku solver. It can solve any provided sokudu puzzle in the form of a n^2 by n^2 grid of integers, where n is a postive integer, with the number 0 serving as a placeholder for blank grid cells. Below is an example Soduku of size 3^2 by 3^2 = 9 by 9 input on the left, and its solution output on the right:
```
003020600		 483921657 
900305001		 967345821 
001806400		 251876493 
008102900		 548132976 
700000008		 729564138 
006708200		 136798245 
002609500		 372689514 
800203009		 814254769 
005010300		 695417382
```
## Design
The `main` function resides in `sodukuSolver.cpp`, in which an instance of the class `Soduku` will be created. All of the search functions used to find a solution will be implemented within `Soduku`. The `Soduku` class also utilizes several data structures, including but not limited to AVL trees, hash tables, queues, stacks, priority queues, and maps (this will be completely replaced by hash tables in the final version).

The variables in `Soduku`, which are the individual grid cells, are implemented as instances of the `Coord` object, short for coordinates. It simply holds two integers x and y that specify where in the grid this object refers to.

## Data Structures
### AVLTree.h
An [AVL tree](https://en.wikipedia.org/wiki/AVL_tree) is a self-balancing binary search tree. This tree is designed to hold the domain, or possible values, each variable in the grid can hold. To initialize an `AVLTree` object:
	```c++
	#include "AVLTree.h"
	// ...
	AVLTree<ElemType> avl;
	```

The things it can do:
1. Add an element
	```c++
	avl.add(item)
	```
2. Remove an element (without returning)
	```c++
	avl.remove(item);
	```
3. Check if it contains an element in O(n) time (returns a bool)
	```c++
	if (avl.contains(item)) {
		// ...
	}
	```
3. Check if its empty (returns a bool)
	```c++
	if (avl.empty()) {
	 // ...
	}
	```
4. Get the size of the tree
	```c++
	int size = avl.size()
	```
5. Get the root of the tree (without removing)
	```c++
	ElemType item = avl.getRoot()
	```
7. Get all the elements in the tree as a stack (This is mostly for convenience at the moment, might be eliminated in the final version)
	```c++
	#include <cstdlib>
	#include <stack>
	// ...
	stack<ElemType> elements = avl.getElements()
	```
6. Print the elements in the tree via in order traversal
	```c++
	avl.print()
	```
7. Print the tree with a bunch of brackets indicating parent-child relationship. This is mostly for debugging at the moment and will probably be removed later.
	```c++
	avl.printTree()
	```

## Usage

## Current progress

## Read more
Please see the doc Julie Jiang Comp 15 Final Project Specs.pdf for formal definitions and algorithms rendered in beautiful LaTeX.