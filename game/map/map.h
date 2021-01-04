#pragma once

#include "../common.h"

//Map is divided in grid which contains players, NPCs, items etc. 
class Map
{
public:

	Map(const std::vector<std::shared_ptr<Grid>>& grids);

	//Calls update for every grid map has. 
	void Update() const;

	friend std::ostream& operator<<(std::ostream& os, const Map& map);

	//Gets grid by name.
	std::shared_ptr<Grid> GetGrid(const std::string& name) const;

	//Gets every entity. Mainly for server communicate information to clients.  
	const std::vector<std::shared_ptr<Entity>> GetNpcs() const;

private:

	std::vector<std::shared_ptr<Grid>> _grids;
};
