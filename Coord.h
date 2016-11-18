#ifndef COORD_H
#define COORD_H

class Coord {
	public:
		Coord(int, int);
		bool Coord &operator==(const Coord &);

	private:
		int x;
		int y;
}

#endif

Coord::Coord(int i, int j) {
	x = i;
	y = j;
}
bool Coord &Coord::operator==(const Coord &source) 
{
	return (x == source.x and y == source.y);
}