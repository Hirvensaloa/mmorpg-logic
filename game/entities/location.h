#pragma once

#include "../common.h"

class Grid; 

//Entities including players have location struct which tells where they are located. 
struct Location
{
	int x;
	int y;
	std::shared_ptr<Grid> grid;

	Location(int _x, int _y, std::shared_ptr<Grid> _grid);

	friend std::ostream& operator<<(std::ostream& os, const Location& location);

	bool operator==(const Location& location);
};