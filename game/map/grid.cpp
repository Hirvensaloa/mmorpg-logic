#include <algorithm>
#include "../common.h"

Grid::Grid(const std::string& name)
	: _name(Util::toLower(name)), _entities(GetEntities()), _hasPlayers(HasPlayers()) 
{
	Log::PrintCreation<Grid>(*this);
}

void Grid::AddTiles(const std::vector<std::vector<Tile>> tiles)
{
	_tiles = tiles; 
}

const std::string& Grid::GetName() const { return _name; }

void Grid::Update()
{
	//Update only if grid has players. 
	if (_hasPlayers)
	{
		//Copy list because original list might change while iterating. 
		std::list<std::shared_ptr<Entity>> entities = _entities;

		auto it = entities.begin();

		while(it != entities.end())
		{
			std::shared_ptr<Entity>& ent = *it;

			if (ent->IsAlive())
			{
				ent->Act();

				it++;
			}
			else
			{
				if (ent->GetType() != Entity::entType::player) //Game handles player removing.
				{
					Log::PrintRemove(ent);

					this->RemoveEntity(ent);
				}

				it++;
			}
		}

	}
}

bool Grid::HasPlayers()
{
	auto it = _entities.cbegin();

	while (it != _entities.cend())
	{
		if ((*it)->GetType() == Entity::entType::player)
			return true; 

		it++;
	}

	return false; 
}

bool Grid::AddEntity(const std::shared_ptr<Entity>& ent, const int& x, const int& y)
{ 
	bool ret; 

	if (_tiles[y][x].AddEntity(ent))
	{
		_entities.push_back(ent);

		//If entity added is a player, set _hasPlayers to true.  
		if (ent->GetType() == Entity::entType::player)
		{
			_hasPlayers = true;
		}

		Game::hasChanged = true;
		ret = true; 
	}
	else
	{
		ret = false; 
	}

	std::stringstream ss;
	ss << "adding entity " << *ent << " to " << " x=" << x << " y=" << y; 
	Log::PrintAction(ss.str() , *this, ret);

	return ret; 
}

bool Grid::MoveEntity(Entity& ent, Location& location)
{
	int x = location.x;
	int y = location.y; 

	std::shared_ptr<Entity> entity = GetEntity(ent.GetType(), ent.GetId());

	if (ValidCoords(x, y) && entity != nullptr && _tiles[y][x].isAccessible())
	{

		this->RemoveEntity(entity);

		//If this == grid entity is moving inside this grid and no need to transfer entity between grids. 
		if (*this == *location.grid)
		{
			this->AddEntity(entity, x, y);
		}
		else
		{
			location.grid->AddEntity(entity, x, y);
		}

		return true;
	}
	else
	{
		std::cout << " (Not valid coords: x= " << x << " y=" << y << ", entity not found or tile not accessible) ";
		return false; 
	}

}



void Grid::RemoveEntity(const std::shared_ptr<Entity>& ent)
{
	const Location& location = ent->GetLocation();

	_tiles[location.y][location.x].RemoveEntity(ent);

	auto it = std::find(_entities.begin(), _entities.end(), ent);

	if (it != _entities.end())
	{
		_entities.erase(it);

		//If entity removed was a player, check if grid contains players anymore. 
		if (ent->GetType() == Entity::entType::player)
			_hasPlayers = HasPlayers();

		Game::hasChanged = true;
	}

}

const std::list<std::shared_ptr<Entity>> Grid::GetEntities() const
{

	std::list<std::shared_ptr<Entity>> entities;

	auto it = _tiles.cbegin();

	while (it != _tiles.cend())
	{
		auto tile_it = it->cbegin();

		while (tile_it != it->cend())
		{
			
			auto ent_it = tile_it->GetEntities().cbegin();
			auto cend = tile_it->GetEntities().cend();

			while (ent_it != cend)
			{
				entities.push_back(*ent_it);

				ent_it++;
			}

			tile_it++;

		}

		it++;
	}

	return entities; 

}

std::vector<Tile> Grid::Neighbours(const int x, const int y)
{

	std::vector<Tile> neighbours;

	int yItr = y - 1; 

	while (yItr <= y + 1)
	{
		int xItr = x - 1;

		while (xItr <= x + 1)
		{
			if (ValidCoords(xItr, yItr) && !(xItr == x && yItr == y))
			{
				neighbours.push_back(_tiles[yItr][xItr]);
			}

			xItr++;
		}

		yItr++;
	}

	return neighbours;

}


std::shared_ptr<Entity> Grid::GetEntity(const Entity::entType& type, const int& id)
{
	auto it = _entities.begin();

	while (it != _entities.end())
	{
		if ((*it)->GetType() == type && (*it)->GetId() == id)
		{
			break;
		}

		it++; 
	}

	if (it != _entities.end())
	{
		return *it; 
	}
	else
	{
		return nullptr; 
	}


}

bool Grid::ValidCoords(int x, int y)
{
	if (!_tiles.empty() && !_tiles[0].empty() && x >= 0 && y >= 0 && x < (int)_tiles[0].size() && y < (int)_tiles.size())
		return true;
	else
		return false;
}

bool Grid::operator==(const Grid& grid)
{
	if (_name == grid._name)
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const Grid& grid)
{

	os << "Grid: " << grid._name << " and size " << grid._tiles.size() << "x" << grid._tiles.size() << " has players = " << grid._hasPlayers;

	return os; 
}

void Grid::GetState(std::ostream& os) const
{

	auto it = _tiles.cbegin();
	
	while (it != _tiles.end())
	{
		auto tileIt = it->cbegin();

		while (tileIt != it->cend())
		{
			if (tileIt->isAccessible())
				os << "O";
			else
				os << "-";

			os << ' ';

			tileIt++; 
		}

		os << "\n";

		it++; 
	}
}

std::queue<Location> Grid::GeneratePath(const Location& start, const Location& end)
{
	std::queue<Location> pathQueue; 

	//If not correct coords return empty queue. 
	if (!ValidCoords(start.x, start.y) || !ValidCoords(end.x, end.y))
		return pathQueue;

	int startx = start.x;
	int starty = start.y; 

	bool isStuck = false;

	while (!isStuck && !(startx == end.x && starty == end.y))
	{

		int ydir = end.y - starty;
		int xdir = end.x - startx;

		//If 1, try to move in y direction first else x direction. 
		int yrand = rand() % 2;

		//For comparison in the end of loop
		int xcmp = startx; 
		int ycmp = starty; 

		if (yrand && ydir != 0)
		{

			if (ydir > 0 && IsAccessible(startx, starty + 1))
			{
				starty++;
				pathQueue.push(_tiles[starty][startx].GetLocation());
			}
			else
			{
				if (IsAccessible(startx, starty - 1) && ydir < 0)
				{
					starty--;
					pathQueue.push(_tiles[starty][startx].GetLocation());
				}
			}

		}

		if (xdir > 0 && IsAccessible(startx + 1, starty))
		{
			startx++;
			pathQueue.push(_tiles[starty][startx].GetLocation());
		}
		else
		{
			if (IsAccessible(startx - 1, starty) && xdir < 0 )
			{
				startx--;
				pathQueue.push(_tiles[starty][startx].GetLocation());
			}
		}
		

		//Check if there is no path to be found.
		if (yrand && xcmp == startx && ycmp == starty)
			isStuck = true; 

	}

	return pathQueue; 
}

bool Grid::IsAccessible(int x, int y)
{
	if (ValidCoords(x, y) && _tiles[y][x].isAccessible())
		return true;
	else
		return false; 
}






