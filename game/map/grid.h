#pragma once

#include "../common.h"

//Map is divided in to Grids. Grid represents a certain area in the map. Grid is divided to Tiles. 
class Grid : std::enable_shared_from_this<Grid>
{
public:

	Grid(const std::string& name);

	const std::string& GetName() const;

	//Updates Grid, goes through every npc and monster and calls their Act() function. 
	void Update();

	//Checks whether there are players in the grid or not. 
	bool HasPlayers();

	//Collects all the entities from grid and returns them in a list. 
	const std::list<std::shared_ptr<Entity>> GetEntities() const;
	
	//Adds tiles to grids. 
	void AddTiles(const std::vector<std::vector<Tile>> tiles);

	//Methods to handle entity movement inside the grid, also entering and exiting handled.
	bool AddEntity(const std::shared_ptr<Entity>& ent, const int& x, const int& y);
	void RemoveEntity(const std::shared_ptr<Entity>& ent);
	bool MoveEntity(Entity& ent, Location& location);

	//Returns neighbouring tiles from given coordinates. 
	std::vector<Tile> Neighbours(const int x, const int y);

	//Checks if coordinates are valid. 
	bool ValidCoords(int x, int y);

	//Checks if coordinates are valid and is possible to access it. 
	bool IsAccessible(int x, int y);

	//Grids are same if they have the same name. Game has only unique area names. 
	bool operator==(const Grid& grid);

	friend std::ostream& operator<<(std::ostream& os, const Grid& grid);

	//Prints the objects state to os. 
	void GetState(std::ostream& os) const;

	//Finds entity by id and type. Returns shared pointer to entity and nullptr if not found.
	std::shared_ptr<Entity> GetEntity(const Entity::entType& type, const int& id);

	//Tries to find path between two locations. If there is no path function returns partial path. 
	std::queue<Location> GeneratePath(const Location& start, const Location& end);

private:

	std::string _name;
	std::vector<std::vector<Tile>> _tiles = std::vector<std::vector<Tile>>();

	//List contains all entities in the grid.
	std::list<std::shared_ptr<Entity>> _entities;

	//Tells if grid contains players or not, used for deciding whether to update grid or not. 
	bool _hasPlayers; 

};