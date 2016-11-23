#include <iostream>
#include "LinkedList.h"
#include "../Coord/Coord.h"
int main()
{
	LinkedList<std::string, int> list;
	
	list.insert("key1", 1);
	list.insert("key2", 2);
	
	int val1 = list["key1"];
	int val2 = list["key2"];
	std::cout << "val1 = " << val1 << " val2 = " << val2 << std::endl;
	LinkedList<Coord, int> list2;
    Coord c1(0, 0);
    Coord c2(4, 7);
    
    list2.insert(c1, 10);
    list2.insert(c2, 20);
   	int val11 = list2[c1];
    
    int val22 = list2[c2];
    std::cout << "val11 = " << val11 << " val22 = " << val22 << std::endl;

    for (LinkedList<Coord, int>::iterator it = list2.begin(); it != list2.end(); ++it) {
    	Coord c = it.key();
    	int value = it.value();
    	std::cout << "c = " << c << " value = " << value << std::endl;
    }

   

	


}