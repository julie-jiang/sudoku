#include <iostream>
#include "HashTable.h"

int main ()
{
	HashTable<std::string, int> *ht = new HashTable<std::string, int>;
	ht->set("a", 1);
	ht->set("b", 2);
	int aval = ht->get("a");
	int bval = ht->get("b");
	std::cout << "aval = " << aval << " bval = " << bval << std::endl;
	typedef std::pair<int, int> Coord;
	/*HashTable<Coord, int> *ht1 = new HashTable<Coord, int>;
	Coord c1 = std::make_pair(0, 0);
	Coord c2 = std::make_pair(4, 7);
	ht1->set(c1, 10);
	ht1->set(c2, 20);*/
	//int aaval = ht->get(c1);
	//int bbval = ht->get(c2);

	return 0;
}