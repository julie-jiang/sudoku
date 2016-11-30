/* 
   Soduku_Solver.cpp
   Implementations for the Soduku_Solver class, a class derived from Soduku.
   This class can solve a soduku puzzle of any size.
 
   By:   Julie Jiang
   UTLN: yjiang06
   Comp 15 Fall 2016 Independent Project
 */
/*****************************************************************************/
/*                                 Usage                                     */
/*****************************************************************************/
/* To solve a puzzle, create an instance of Soduku with the parametrized 
   constructor, and provide a path to a file that contains an unsolved soduku 
   puzzle:
        Soduku soduku(puzzle.txt);
   To print the (complete or incomplete) solutions to terminal:
        soduku.print();
   To output the solutions to a file:
        soduku.write(filename.txt);
   For both of these options, if the puzzle is only partially solved, then
   grid cells with indeterminate values will be printed as bold red '0'.
 */
/*****************************************************************************/
/*                         Containers Explained                              */
/*****************************************************************************/
/* A Coord is an object that holds two integers that indicates the coordinates
   of a variable in a Soduku puzzle grid.
  
   A unit is defined to be a set of Coords a row, column, or subgrid. In a 
   typical 9 by 9 Soduku puzzle, there are 9 rows + 9 columns + 9 subgrids = 
   27 units. 
  
   The following containers will be used throughout Soduku_Solver:
  
   1. "allunits" is a vector of vector of Coords. It contains a list of all the
       units in the puzzle in terms of Coords.
   2. "units" is a map that maps a Coord to the three units that contains that
       Coord.
   3. "peers" is a map that maps a Coord to all the other Coords that share
      a common unit.
   4. "puzzle" is a map that maps a Coord to its initial value in the provided
      file. 
   5. "domains" is a map that maps a Coord to its remaining legal values. 
      Throughout the search algorithms, many different copies of "domains" will 
      be passed around so as to not get all the search states mixed up. There 
      is also a member variable called domains, which I will refer to as 
      this->domains.
 */
#include <iostream>
#include <fstream>
#include "Soduku_Solver.h"
#include "Coord/Coord.h"
#include "HashTable/HashTable.h"
#include "Set/Set.h"
#include "Soduku_Util.h" // get_raw_name 
/*****************************************************************************/
/*                             Public Functions                              */
/*****************************************************************************/
/* Parameterized constructor. 
   Initializes a Soduku object and attempts to solve it.*/
Soduku_Solver::Soduku_Solver(std::string filename)
{
    puzzle_name = filename;
    read_puzzle();
    init_containers();
    solve();
}

/* Print the solved or incomplete soduku puzzle as a 2D grid. The assigned 
   value of each grid cell is printed via standard cout. If the solution 
   is incomplete, then the grid cells that don't have assigned values will be 
   have '0' printed instead in bold red.
   This is printed with gridlines!  */
void Soduku_Solver::print_solution()
{
    int max_char_length = get_num_digits(gridSize);
    std::string *whitespace = get_whitespaces(max_char_length);

    for (size_t j = 0; j < gridSize; j++) {
        if (j % n == 0) {
            print_horizontal_line(max_char_length);
        }
        std::cout << "| ";
        for (size_t i = 0; i < gridSize; i++) {
            Coord c(i, j);
            if (this->domains[c].size() == 1) {
                int number= this->domains[c].top();
                std::cout << number << whitespace[get_num_digits(number) - 1];
            } else {
                std::cout << "\033[1m\033[31m0\033[0m" << whitespace[0];
            }
            if ((i + 1) % n == 0) {
                std::cout << "| ";
            }
        } std::cout << std::endl;
    }
    print_horizontal_line(max_char_length);
    delete [] whitespace;
}
/* Write the solutions to the specified directory as a .txt file. 
   Files will be named the same as their original filename + "_solutions". 
   For example, if the original puzzle name was called "some_puzzle.txt" then
   the output file will be called "some_puzzle_solutions.txt". 

   The puzzle will be written without gridlines and with 0 in place of any 
   grid cells with indeterminate values.
    
   Throws logic error if the directory does not exist. */
void Soduku_Solver::write_solution(std::string directory)
{
    // Open file
    std::string rawname = get_raw_name(puzzle_name);
    std::string filename = directory + "/" + rawname +"_solution.txt";
    std::ofstream outFile(filename);
    if (not outFile.is_open()) {
        throw std::logic_error("ERROR: " + directory + 
                               " is not a valid directory");
    }
    // Write to file
    int max_char_length = get_num_digits(gridSize);
    std::string *whitespace = get_whitespaces(max_char_length);
    for (size_t j = 0; j < gridSize; j++) {
        for (size_t i = 0; i < gridSize; i++) {
            Coord c(i, j);
            if (this->domains[c].size() == 1) {
                int number= this->domains[c].top();
                outFile << number << whitespace[get_num_digits(number) - 1];
            } else {
                outFile << "0 " << whitespace[0];
            }
        } outFile << std::endl;
    }
    outFile.close();
    
}

/*****************************************************************************/
/*                              Solve Puzzle                                 */
/*****************************************************************************/

/* Solve a soduku puzzle by first pruning the grid, then using a depth-first, 
   backtracking search algorithm to find a solution.
   Returns true is a solution is found. */
bool Soduku_Solver::solve()
{
    // Return false if any contradiction is found while pruning the grid
    if (not prune_grid()) {
        return false;
    }
    HashTable<Coord, Set<int>> copy_domains(this->domains);
    bool result = search(copy_domains);
    this->domains = copy_domains;
    return result;
}

/* Prune the grid by assigning values as indicated by the initial puzzle. 
   Enforce constraint consistency for each value assigned. 
   Returns false if any contradictions arises. */
bool Soduku_Solver::prune_grid()
{
    for (HashTable<Coord, int>::iterator it = puzzle->begin();
         it != puzzle->end(); ++it) {
        Coord c = it.key();
        int   d = it.value();
        // If d is an assigned value and assignment failed, return false.
        if (d != 0 and not assign(this->domains, c, d)) {
            return false;
        }
    }
    return true;
}
/*****************************************************************************/
/*                           Backtracking search                             */
/*****************************************************************************/
/*
 * A depth-first backtracking search algorithm. 
 */
bool Soduku_Solver::search(HashTable<Coord, Set<int>> &domains)
{
    // If it is solved, then no need to go further
    if (solved(domains)) {
        return true;
    } 
    
    Coord c = select_unassigned_variable(domains);
    
    // Try all the domains. For each domain, enforce constraint consistency. 
    // Use a new copy of domains for every recursion. 
    Set<int> domains_of_c(domains[c]);
    
    while (not domains_of_c.empty()) {
        int d = domains_of_c.pop();
        HashTable<Coord, Set<int>> copy_domains(domains);
        if (assign(copy_domains, c, d) and search(copy_domains)) {
            domains = copy_domains;
            return true;
        } // If assignment or recursive search didn't work, keep trying until 
          // domains_of_c is not empty    
        //delete copy_domains;    
    }
    // If none of the values in the domain works, then return false.
    
    return false;
}

/*
 * Return true if puzzle is solved. A puzzle is considered solved if there is
 * one and only one value in the domain of every Coord.
 */
bool Soduku_Solver::solved(HashTable<Coord, Set<int>> &domains) 
{
    int i = 1; 
    for (HashTable<Coord, Set<int>>::iterator it = domains.begin(); 
         it != domains.end(); ++it) {
        size_t size = it.value().size();
        i++;
        if (size != 1) {
            return false;
        }
        assert(size > 0); // Sanity check
    }
    return true;
}

/*
 * Select an unassigned variable according to the minimum value heuristic.
 * That is, select one with the least number of possible values.
 * Return the selected variable, or Coord.
 */
Coord Soduku_Solver::select_unassigned_variable(
                                            HashTable<Coord, Set<int>> &domains)
{
    // Begin with a dummy Coord object. This Coord don't exist in the real 
    // puzzle.
    Coord c(gridSize, gridSize);
    size_t min_size = gridSize + 1;

    // Iterate through the domain to find the one smallest in size.
    for (HashTable<Coord, Set<int>>::iterator it = domains.begin();
         it != domains.end(); ++it) {
        size_t size = it.value().size();

        // Variables (Coords) with domains of size == 1 are considered 
        // assigned variables. So we look for ones that are > 1.
        if (size > 1 and size < min_size) {
            min_size = size;
            c = it.key();
        }
    }

    // Assert that c is not still the dummy Coord;
    assert(c[0] != (int) gridSize);
    return c;
}
/*****************************************************************************/
/*                         Constraint Propagation                            */
/*****************************************************************************/
/*
 * Assign Coord c to a value d by eliminating all other values from its domain.
 * Return true if assignment is successful
 */
bool Soduku_Solver::assign(HashTable<Coord, Set<int>> &domains, Coord c, int d)
{
    Set<int> *other_domains = new Set<int>(domains[c]);
    while (not other_domains->empty()) {
        int d2 = other_domains->pop();

        // Skip d2 == d because we don't want to remove d from c.
        // Return false if eiminating d2 from c is unsuccessful.
        if (d2 != d and not eliminate(domains, c, d2)) {
            return false;
        }
    }
    delete other_domains;
    return true;
}
/*
 * Eliminate a value d from the domain of a Coord c by first removing d from 
 * domain[c], then enforce constraint consistency. Constraint consistency is
 * enforced in two steps.
 *      1) If d is the only value left in the domain of c, then eliminate d 
 *         from the domains of all of c's peers. 
 *      2) For every unit that contains c, if there is only one place Coord for 
 *         which that d can be assigned to, then assign that Coord to d.
 * Return true if elimination is successful.
 */
bool Soduku_Solver::eliminate(HashTable<Coord, Set<int>> &domains, Coord c, 
                              int d)
{
    // No need to go any further if d is already not contained in c's domain
    if (not domains[c].contains(d)) {
        return true;
    }
    domains[c].remove(d);

    // Domain should not be empty
    if (domains[c].empty()) {
        return false;
    } 
    // Return false if either (1) or (2) is not satisfied
    if ((not (eliminate_from_peers(domains, c))) or 
         not (check_unique_remaining_values(domains, c, d))) {
        return false;
    }
    return true;
}
/*
 * First step in the two step process of constraint propagation. 
 * If d is the only value left in the domain of c, then eliminate d from the 
 * domains of all of c's peers. 
 * Return true if elimination is successful
 */
bool Soduku_Solver::eliminate_from_peers(HashTable<Coord, Set<int>> &domains, 
                                         Coord c)
{

    if (domains[c].size() == 1) {
        int d = domains[c].top();
        for (Set<Coord>::iterator it = (*peers)[c].begin(); 
             it != (*peers)[c].end(); ++it) {
            Coord c2 = *it;
            // Return false if eliminating d from c2 is unsuccessful
            if (not eliminate(domains, c2, d)) {
                return false;
            }
        }
    }
    return true;
}

/*
 * Second step in the two step process of constraint propagation. 
 * For every unit that contains c, if there is only one place Coord for 
 * which that d can be assigned to, then assign that Coord to d.
 * Return true if no contradiction is found.
 */
bool Soduku_Solver::check_unique_remaining_values(
                           HashTable<Coord, Set<int>> &domains, Coord c, int d)
{
    // For each unit that contains c
    for (size_t i = 0; i < (*units)[c].size(); i++) {
        // Obtain a list of possible places that int d can be
        std::vector<Coord> possible_places; 
        for (size_t j = 0; j < (*units)[c][i].size(); j++) {
            Coord c2 = (*units)[c][i][j];
            if (domains[c2].contains(d)) {
                possible_places.push_back(c2);
            } 
        }

            // Contradiction if d cannot exist anywehre.
        if ((possible_places.size() == 0) or 
            // If d can only exist in one place, then assign that Coord to d.
            // Return false if assignment failed.
            (possible_places.size() == 1 and 
             (not assign(domains, possible_places[0], d)))) {
                return false; 
            }
    }
    return true;
}
/*****************************************************************************/
/*                               Initialization                              */
/*****************************************************************************/
/*
 * Initialize other data structures.
 * "allunits" contains a list of the units in the puzzle. A unit contains a 
 * list of a set of coordinates that lie in the same row, column, or n by n 
 * subgrid.
 * "units" maps a Coord (a set of coordinates) to all the units that contain
 * that Coord.
 * "peers" maps a Coord to all the other Coords that share a common unit.
 */
void Soduku_Solver::init_containers()
{
    units = new HashTable<Coord, std::vector<std::vector<Coord>>>(container_size);
    peers = new HashTable<Coord, Set<Coord>>(container_size);
    domains.resize(container_size);

    std::vector<std::vector<Coord>> allunits;
    for (size_t j = 0; j < gridSize; j++) {
        allunits.push_back(std::vector<Coord>());
        allunits.push_back(std::vector<Coord>());
        for (size_t i = 0; i < gridSize; i++) {
            Coord c1(i, j); Coord c2(j, i);
            allunits[2 * j].push_back(c1);
            allunits[2 * j + 1].push_back(c2);
            units->insert(c1, std::vector<std::vector<Coord>>());
            peers->insert(c1, Set<Coord>()); 
            this->domains.insert(c1, Set<int>(*new_unit())); }} // TODO: memory link?

    for (size_t i = 0; i < gridSize; i += n) {
        for (size_t j = 0; j < gridSize; j += n) {
            allunits.push_back(std::vector<Coord>());
            size_t size = allunits.size();
            for (size_t k = i; k < n + i; k++) {
                for (size_t l = j; l < n + j; l++) {
                    Coord c(l, k);
                    allunits[size - 1].push_back(c); }}}} 

    for (size_t i = 0; i < allunits.size(); i++) {
        for (size_t j = 0; j < allunits[i].size(); j++) {
            Coord c = allunits[i][j];
            (*units)[c].push_back(std::vector<Coord>(allunits[i]));
            for (size_t k = 0; k < allunits[i].size(); k++) {
                if (k != j) {
                    Coord c2 = allunits[i][k];
                    (*peers)[c].add(c2); }}}}
    
}
/*****************************************************************************/
/*                           Utility Functions                               */
/*****************************************************************************/
Soduku_Solver::~Soduku_Solver()
{
    delete units;
    delete peers;
}


/*
 * Print the remaining legal values of each Coord. For debugging purposes.
 */
void Soduku_Solver::printDomains(HashTable<Coord, Set<int>> &domains)
{
    for (size_t j = 0; j < gridSize; j++) {
        for (size_t i = 0; i < gridSize; i++) {
            Coord c(i, j);
            std::cout << c << " = " << domains[c] << "\n";
        }
        std::cout << std::endl;
    }
}

