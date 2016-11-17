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
	return 0;
}