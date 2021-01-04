#pragma once

#include <fstream>
#include <exception>
#include <ctype.h>
#include "../common.h"

//Responsible for creating game instance

namespace Loader
{

	std::string toLower(const std::string& str)
	{
		std::string data = str;
		std::transform(data.begin(), data.end(), data.begin(),
			[](unsigned char c) { return std::tolower(c); });

		return data; 
	}

	//Exception to throw when file is corrupted. Takes filename as parameter which tells where the error happened. 
	class FileCorruptedException : public std::exception {
	public:

		FileCorruptedException(const std::string& filename, const std::string& reason) 
			: _message(filename + " file corrupted : " + reason) {}

		virtual const char* what() const throw () {
			return _message.c_str();
		}

	private:
		
		std::string _message; 
	};

	//Functions wrapped inside anonymous namespace protects them from getting called elsewhere than Log namespace. 
	namespace
	{

		//Loads tiles from line to vector. Throws exception if line is ill-formed. 
		void LoadTiles(std::vector<std::vector<Tile>>& tiles, const std::string& line, const std::shared_ptr<Grid> grid)
		{

			auto it = line.cbegin();

			std::vector<Tile> tileRow;
			unsigned int y = static_cast<int>(tiles.size());

			while (it != line.cend())
			{
				const char lowercase = std::tolower(*it);

				int x = static_cast<int>(tileRow.size());

				switch (lowercase)
				{
				case 'o':
					tileRow.push_back(Tile(true, Location(x, y, grid)));
					break;
				case '-':
					tileRow.push_back(Tile(false, Location(x, y, grid)));
					break;
				case ' ':
					break;
				default:
					throw FileCorruptedException("Grid", "Loading tiles failed");
				}

				it++;
			}

			tiles.push_back(tileRow);

		}

		std::shared_ptr<Grid> LoadGrid(std::ifstream& infile, const std::string& name)
		{
			std::shared_ptr<Grid> newGrid = std::make_shared<Grid>(Grid(name));

			std::vector<std::vector<Tile>> tiles;

			std::string line;

			while (std::getline(infile >> std::ws, line))
			{
				if (!line.empty())
				{
					if (line[0] == '#')
						break;
					else
						LoadTiles(tiles, line, newGrid);
				}
			}

			newGrid->AddTiles(tiles);

			unsigned int size = static_cast<int>(tiles.size());

			auto it = std::find_if(tiles.cbegin(), tiles.cend(),
				[&](const std::vector<Tile>& tile)
				{
					return tile.size() != size; 
				}
			);

			if (it != tiles.cend())
				throw FileCorruptedException("Grid", "Grid is not a square");

			//Throw exception if file is corrupted. 
			if (line.empty() || line[0] != '#')
				throw FileCorruptedException("Grid", name);
			else
				return newGrid;
		}


		//Loads grids and returns them. 
		std::vector<std::shared_ptr<Grid>> LoadGrids()
		{
			std::vector<std::shared_ptr<Grid>> grids;

			std::ifstream infile;

			try
			{
				infile.open("game/gamefiles/grids.txt");

				std::string line; 

				while (std::getline(infile >> std::ws, line))
				{
					if (!line.empty() && line[0] == '#')
					{
						std::string name = line.erase(0, 1);

						std::shared_ptr<Grid> newGrid = LoadGrid(infile, name);

						grids.push_back(newGrid);
					}

				}

			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}

			infile.close();


			return grids; 
		}

		//Loads single entity from given line. 
		void LoadEntity(const Map& map, std::string line)
		{
			std::istringstream sstream(line.erase(0, 1));

			std::string type;
			std::string name;
			int x;
			int y;
			std::string gridName;

			if (!(sstream >> type >> name >> x >> y >> gridName))
				throw FileCorruptedException("Entities", "Incorrect format");

			std::shared_ptr<Grid> grid = map.GetGrid(gridName);

			//Return if there is no such grid.
			if (grid == nullptr)
				throw FileCorruptedException("Entities", "no grid found for " + name);

			Location location = Location(x, y, grid);

			if (type == "monster")
			{
				int dmg;
				int hp;

				if ((sstream >> dmg >> hp))
				{
					std::shared_ptr<Entity> monster = std::make_shared<Monster>(Monster(name, location, dmg, hp));

					grid->AddEntity(monster, location.x, location.y);
				}
				else
				{
					throw FileCorruptedException("Entities", "Incorrect format");
				}					

			}
			else if (type == "npc")
			{
				std::shared_ptr<Entity> npc = std::make_shared<Npc>(Npc(name, location));

				grid->AddEntity(npc, location.x, location.y);
			}
			else
			{
				throw FileCorruptedException("Entities", "Typename (" + type  + ") incorrect");
			}

		}

		//Loads entities to grid and tiles. 
		void LoadEntities(const Map& map)
		{
			std::ifstream infile;

			try
			{
				infile.open("game/gamefiles/entities.txt");

				std::string line;

				while (std::getline(infile >> std::ws, line))
				{
					if (!line.empty() && line[0] == '#')
					{
						LoadEntity(map, Util::toLower(line));
					}
				}
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl; 
			}

			infile.close();

		}
	}

	//Loads game
	Game LoadGame()
	{
		Map map = Map(LoadGrids());

		LoadEntities(map);

		return Game(map);
	}


}