/*
 * Implementations of the Soduku class.
 * This class can solve a soduku puzzle of any size.
 *
 * Usage: 
 *      To solve a soduku puzzle, provide a path to a file that contains
 *      valid soduku puzzle: 
 *              Soduku soduku(puzzle.txt);
 *      To see the solutions (if there are any):
 *              soduku.print();
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <cassert>
#include "Soduku.h"
#include "Set/Set.h"
#include "Coord/Coord.h"
#include "HashMap/HashMap.h"
/*****************************************************************************/
/*                             Public Functions                              */
/*****************************************************************************/
/* 
 * Initializes a Soduku object and attempts to solve it.
 */
void Soduku::solve(std::string filename)
{
    puzzle_name = filename;
    read_puzzle();
    init_data_structures();
    solve();
}
bool Soduku::check(std::string filename)
{
    puzzle_name = filename;
    read_puzzle();
    return validate_puzzle();
}

/*
 * Print the solved or incomplete soduku puzzle as a 2D grid. The assigned 
 * value of each Coord is printed via standard cout. If the solution 
 * is incomplete, then the Coords that don't have assigned values will be have
 * '0' printed instead in bold red.
 * This is printed with gridlines!
 */
void Soduku::print()
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
                std::cout << "\033[1m\033[31m0\033[0m ";
            }
            if ((i + 1) % n == 0) {
                std::cout << "| ";
            }
        } std::cout << std::endl;
    }
    print_horizontal_line(max_char_length);
    delete [] whitespace;
}
/*
 * Write the solutions to the specified directory. 
 */

void Soduku::write(std::string directory)
{
    // Open file
    std::string rawname = puzzle_name.substr(0, puzzle_name.find_last_of("."));
    rawname = rawname.substr(puzzle_name.find_last_of("/\\") + 1);
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
                outFile << "\033[1m\033[31m0\033[0m ";
            }
        } outFile << std::endl;
    }
    outFile.close();
}

/*****************************************************************************/
/*                              Solve Puzzle                                 */
/*****************************************************************************/
/*
 * Solve a soduku puzzle by first pruning the grid, then using a depth-first, 
 * backtracking search algorithm to find a solution.
 * Returns true is a solution is found.
 */
bool Soduku::solve()
{
    // Return false if any contradiction is found while pruning the grid
    if (not prune_grid()) {
        return false;
    }
    HashMap<Coord, Set<int>> copy_domains(this->domains);
    bool result = search(copy_domains);
    this->domains = copy_domains;
    return result;
}
/*
 * Prune the grid by assigning values as indicated by the inititial puzzle. 
 * Enforce constraint consistency for each value assigned.
 * Returns false if any contradictions arises.
 */
bool Soduku::prune_grid()
{
    for(HashMap<Coord, int>::key_iterator key = puzzle.begin();
        key != puzzle.end(); ++key) {
        Coord c = *key;
        int   d = puzzle[c];
        // If d is an assigned value and assignment failed, return false.
        if (d != 0 and not assign(this->domains, c, d)) {
            return false;
        }
    }
    return true;
}

/*****************************************************************************/
/*                           Validate Puzzle                                 */
/*****************************************************************************/
bool Soduku::validate_puzzle()
{
    for (size_t j = 0; j < gridSize; j++) {
        allunits.push_back(std::vector<Coord>());
        allunits.push_back(std::vector<Coord>());
        for (size_t i = 0; i < gridSize; i++) {
            Coord c1(i, j); Coord c2(j, i);
            allunits[2 * j].push_back(c1);
            allunits[2 * j + 1].push_back(c2);

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
            units[c].push_back(std::vector<Coord>(allunits[i]));
            for (size_t k = 0; k < allunits[i].size(); k++) {
                if (k != j) {
                    Coord c2 = allunits[i][k];

}
/*****************************************************************************/
/*                           Backtracking search                             */
/*****************************************************************************/
/*
 * A depth-first backtracking search algorithm. 
 */
bool Soduku::search(HashMap<Coord, Set<int>> &domains)
{
    // If it is solved, then no need to go further
    if (solved(domains)) {
        return true;
    } 

    Coord c = select_unassigned_variable(domains);

    // Try all the domains. For each domain, enforce constraint consistency. 
    // Use a new copy of domains for every recursion. 
    Set<int> c_domains(domains[c]);
    while (not c_domains.empty()) {
        int d = c_domains.pop();
        HashMap<Coord, Set<int>> copy_domains(domains);
        if (assign(copy_domains, c, d) and search(copy_domains)) {
            domains = copy_domains;
            return true;
        }        
    }
    // If none of the values in the domain works, then return false.
    return false;
}

/*
 * Return true if puzzle is solved. A puzzle is solved if there is one
 * and only one value in the domain of every Coord.
 */
bool Soduku::solved(HashMap<Coord, Set<int>> &domains) 
{
    for (HashMap<Coord, Set<int>>::key_iterator key = domains.begin(); 
         key != domains.end(); ++key) {
        size_t size = domains[*key].size();
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
Coord Soduku::select_unassigned_variable(HashMap<Coord, Set<int>> &domains)
{
    // Begin with a dummy c. This Coord don't exist in the real puzzle.
    Coord c(gridSize, gridSize);
    size_t min_size = gridSize + 1;

    // Iterate through the domain to find the one smallest in size.
    for (HashMap<Coord, Set<int>>::key_iterator it = domains.begin();
         it != domains.end(); ++it) {
        size_t size = domains[*it].size();

        // Variables (Coords) with domains of size == 1 are considered 
        // assigned variables. So we look for ones that are > 1.
        if (size > 1 and size < min_size) {
            min_size = size;
            c = *it;
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
 * Return true if no contradiction is found.
 */
bool Soduku::assign(HashMap<Coord, Set<int>> &domains, Coord c, int d)
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
 *Return true if no contradiction is found.
 */
bool Soduku::eliminate(HashMap<Coord, Set<int>> &domains, Coord c, int d)
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
 * Return true if no contradiction is found.
 */
bool Soduku::eliminate_from_peers(HashMap<Coord, Set<int>> &domains, Coord c)
{

    if (domains[c].size() == 1) {
        int d = domains[c].top();
        for (Set<Coord>::iterator it = peers[c].begin(); 
             it != peers[c].end(); ++it) {
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
bool Soduku::check_unique_remaining_values(HashMap<Coord, Set<int>> &domains, 
                                           Coord c, int d)
{
    // For each unit that contains c
    for (size_t i = 0; i < units[c].size(); i++) {

        // Obtain a list of possible places that int d can be
        std::vector<Coord> possible_places; 
        for (size_t j = 0; j < units[c][i].size(); j++) {
            Coord c2 = units[c][i][j];
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
/*                          Initialization Functions                         */
/*****************************************************************************/
/*
 * Process the input file and convert it into a Soduku puzzle.
 * Throw logic error if the file cannot be opened, or if the file does not 
 * contain a valid Soduku puzzle.
 */
void Soduku::read_puzzle()
{
    // Reset data structures
    reset(); 
    size_t num_elements = 0;
    // Open file 
    std::ifstream inFile;
    inFile.open(puzzle_name);
    if (inFile.fail()) {
        throw std::logic_error("ERROR: File " + puzzle_name + " does not exist");
    }

    // Read input
    std::queue<int> *elements = new std::queue<int>;
    std::string s;
    while (inFile >> s) {
        elements->push(string2int(s));
        num_elements++;
    }
    inFile.close();
    // Get grid size
    gridSize = square_root(num_elements);
    n = square_root(gridSize);

    // Initialize Soduku puzzle grid
    init_grid(*elements);
    delete elements;
}
/*
 * Initialize grid. 
 * "puzzle" maps a set of coordinates to their initial value as given in the 
 * soduku puzzle, be it 0 or 1-9.
 * "domains" maps a set of coordinates to their remaining legal domain values.
 * Here, this is initialized to be all the numbers from 1 to gridSize.
 */
void Soduku::init_grid(std::queue<int> &elements)
{
    // initialize grid
    for (size_t j = 0; j < gridSize; j++) {
        for (size_t i = 0; i < gridSize; i++) {
            Coord c(i, j);
            int num = elements.front();
            elements.pop();
            puzzle.insert(c, num);
            domains.insert(c, Set<int>());
            // Domain can be any number from 1 to gridSize
            for (size_t i = 1; i < gridSize + 1; i++) {
                domains[c].add(i);
            }
        }
    }
}
/*
 * Initialize other data structures.
 * "allunits" contains a list of the units in the puzzle. A unit contains a 
 * list of a set of coordinates that lie in the same row, column, or n by n 
 * subgrid.
 * "units" maps a Coord (a set of coordinates) to all the units that contain
 * that Coord.
 * "peers" maps a Coord to all the other Coords that share a common unit.
 */
void Soduku::init_data_structures()
{
    for (size_t j = 0; j < gridSize; j++) {
        allunits.push_back(std::vector<Coord>());
        allunits.push_back(std::vector<Coord>());
        for (size_t i = 0; i < gridSize; i++) {
            Coord c1(i, j); Coord c2(j, i);
            allunits[2 * j].push_back(c1);
            allunits[2 * j + 1].push_back(c2);
            units.insert(c1, std::vector<std::vector<Coord>>());
            peers.insert(c1, Set<Coord>()); }}

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
            units[c].push_back(std::vector<Coord>(allunits[i]));
            for (size_t k = 0; k < allunits[i].size(); k++) {
                if (k != j) {
                    Coord c2 = allunits[i][k];
                    peers[c].add(c2); }}}}
    
}
void Soduku::reset()
{
    allunits.clear();
    units.clear();
    peers.clear();
    domains.clear();
    puzzle.clear();
}

/*****************************************************************************/
/*                           Utility Functions                               */
/*****************************************************************************/
/*
 * Print the remaining legal values of each Coord. For debugging purposes.
 */
void Soduku::printDomains(HashMap<Coord, Set<int>> &domains)
{
    for (size_t j = 0; j < gridSize; j++) {
        for (size_t i = 0; i < gridSize; i++) {
            Coord c(i, j);
            std::cout << c << " = " << domains[c] << "\n";
        }
        std::cout << std::endl;
    }
}

/*
 * Print helper function. Prints a horizontal line.
 */
void Soduku::print_horizontal_line(int max_char_length)
{
    std::cout << "|";
    size_t length = gridSize * (max_char_length + 1) + n * 2 - 1;
    for (size_t i = 0; i < length; i++) {
        std::cout << "-";
    }
    std::cout <<"| \n";
}

/*
 * Find the square root of the given number. 
 * Throw logic error if no perfect square root can be found.
 */
size_t Soduku::square_root(size_t num)
{
    size_t i = 1;
    while (i <= num / 2 + 1) {
        if (i * i == num) {
            return i;
        }
        if (i * i > num) {
            break;
        }
        i++;
    }
    throw std::logic_error("Error: File " + puzzle_name + 
                           " does not contain valid Soduku puzzle");
}
/*
 * Convert a string to an int. 
 * Throw runtime error if the string is not numerical.
 */
int Soduku::string2int(std::string s)
{
    std::stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw std::logic_error("ERROR: File " + puzzle_name + 
                                 " contains nonnumerical value");

    return result;
}
/*
 * Get the number of digits in the given int */
int Soduku::get_num_digits(int num)
{
    int i = 1;
    int digits = 1;
    while (num / i > 9) {
        i *= 10;
        digits++;
    }
    return digits;
}
std::string *Soduku::get_whitespaces(int max_char_length)
{
    std::string *whitespace = new std::string [max_char_length];
    for (int i = 0; i < max_char_length; i++) {
        whitespace[i] = "";
        for (int j = i; j < max_char_length; j++) {
            whitespace[i] += " ";
        }
    }
    return whitespace;
}


