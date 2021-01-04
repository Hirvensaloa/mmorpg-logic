#include "../common.h"

Location::Location(int _x, int _y, std::shared_ptr<Grid> _grid)
	: x(_x), y(_y), grid(_grid) {}

std::ostream& operator<<(std::ostream& os, const Location& location)
{
	os << "Location: x=" << location.x << " y=" << location.y << " area=" << location.grid->GetName(); 

	return os; 
}

bool Location::operator==(const Location& location)
{
	if (location.x == x && location.y == y && location.grid == grid)
		return true;
	else
		return false; 
}
