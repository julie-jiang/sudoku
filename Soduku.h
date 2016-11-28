#ifndef SODUKU_H
#define SODUKU_H
#include <cstdlib>
#include <vector>
#include <queue>
#include "Set/Set.h"
#include "Coord/Coord.h"
#include "HashMap/HashMap.h"

class Soduku {
    public:
        Soduku(std::string, int);
        ~Soduku();
    private:
        std::vector<std::vector<Coord>> allunits;
        HashMap<Coord, std::vector<std::vector<Coord>>> units;
        HashMap<Coord, Set<Coord>> peers;
        HashMap<Coord, Set<int>> domains;
        HashMap<Coord, int> puzzle;
        int gridSize;
        int n;
        void init_data_structures();
        void init_grid(std::string);
        int string2int(std::string);
        bool solve();
        bool search(HashMap<Coord, Set<int>> &);
        bool solved(HashMap<Coord, Set<int>> &);
        Coord select_unassigned_variable(HashMap<Coord, Set<int>> &);
        bool prune_grid(HashMap<Coord, Set<int>> &);
        bool assign(HashMap<Coord, Set<int>> &, Coord, int);
        bool eliminate(HashMap<Coord, Set<int>>&, Coord, int);
        bool eliminate_from_peers(HashMap<Coord, Set<int>> &, Coord);
        bool check_unique_remaining_values(HashMap<Coord, Set<int>> &, Coord, int);
        void print(HashMap<Coord, Set<int>> &);
        void printDomains(HashMap<Coord, Set<int>> &);


};
#endif