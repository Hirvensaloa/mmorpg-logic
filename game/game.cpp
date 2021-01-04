#include "common.h"

bool Game::hasChanged = false; 

Game::Game(const Map& map)
	: _map(map) 
{
	Log::PrintCreation<Game>(*this);
}

Player& Game::GetPlayer(const int& connection_id)
{
	auto it = _players.find(connection_id);

	return *(*it).second;
}

void Game::RemovePlayer(const int& connection_id)
{
	auto it = _players.find(connection_id); 

	if(it != _players.end())
	{
		std::shared_ptr<Player> player = it->second;

		_players.erase(it);

		player->GetLocation().grid->RemoveEntity(player);
	}

}

void Game::Tick()
{
	_map.Update();

	std::vector<int> toRemove; 

	auto it = _players.begin();

	while (it != _players.end())
	{
		if (!(it->second->IsAlive()))
		{
			Log::PrintRemove(*(it->second));

			toRemove.push_back(it->first);
		}

		it++;
		
	}

	std::for_each(toRemove.cbegin(), toRemove.cend(),
		[&](const int& id)
		{
			RemovePlayer(id);
		}
	);

	Log::PrintAction("tick", *this, true);
}

void Game::AddPlayer(const int& connection_id, const std::shared_ptr<Player>& player) 
{ 
	_players.insert(std::make_pair(connection_id, player)); 
	
	const Location& loc = player->GetLocation();

	loc.grid->AddEntity(player, loc.x, loc.y);
}

const Map& Game::GetMap() const { return _map; }

std::ostream& operator<<(std::ostream& os, const Game& game)
{
	os << "Game"; 

	return os; 
}

const std::map<int, std::shared_ptr<Player>>& Game::GetPlayers()
{
	return _players;
}