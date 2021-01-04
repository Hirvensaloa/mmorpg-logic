#pragma once

#include <map>
#include "common.h"

//Game class contains map which is updated with every tick. 
class Game
{
public:

	static bool hasChanged;

	Game(const Map& map);

	//Updates game state
	void Tick();

	//Adds connection id mapped to its player.
	void AddPlayer(const int& connection_id, const std::shared_ptr<Player>& player);

	//Removes player from the game. 
	void RemovePlayer(const int& connection_id);

	//Get player for connection id. 
	Player& GetPlayer(const int& connection_id);

	const Map& GetMap() const;

	friend std::ostream& operator<<(std::ostream& os, const Game& game);
 
	const std::map<int, std::shared_ptr<Player>>& GetPlayers();

private:

	const Map _map;

	//All the players that are logged in mapped to their id. 
	std::map<int,std::shared_ptr<Player>> _players;
};