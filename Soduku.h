#ifndef SODUKU_H
#define SODUKU_H
#include <cstdlib>
#include <vector>
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
        HashMap<Coord, Set<int>> values;
        HashMap<Coord, int> puzzle;
        int gridSize;
        int n;
        void init(std::string);
        void init_data_structures();
        void init_grid(std::string);
        int string2int(std::string);
        bool solve();
        bool assign(Coord, int);
        bool eliminate(Coord, int);
        void print();


};
#endif