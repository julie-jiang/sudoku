#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	int N = 16;
	int n = (int) sqrt(N);
	cout << "n = " << n << endl;
	int x = 1;
	int y = 2;

	for (int i = x - x % n; i < n + x - x % n; i++) {
		for (int j = y - y % n; j < n + y - y % n; j++) {
			if (i != x and j != y)
				cout << "(" << i << ", " << j << ")" << endl;
		}
	}
}