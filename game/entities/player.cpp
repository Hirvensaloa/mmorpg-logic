#include <stdlib.h>
#include "../common.h"

Player::Player(const int& id, const std::string& name, Location& location, const Skills& skills, const Inventory& inventory)
	: Entity(Entity::entType::player, id, name, location), _skills(skills), _inventory(inventory) {}

bool Player::Attack(Entity& ent)
{
	bool ret; 

	const std::vector<Tile> neighbours = _location.grid->Neighbours(_location.x, _location.y);

	auto it = std::find_if(neighbours.begin(), neighbours.end(),
		[&](const Tile& tile)
		{
			return tile.ContainsEntity(ent);
		}
	);

	unsigned int dmg = _skills.GetDmg();

	if (it != neighbours.end())
	{
		ent.ReduceHP(dmg);

		ret = true; 
	}
	else
	{
		ret = false; 
	}

	Log::PrintAction("attack by player " + _name + " dmg=" + (char)dmg, ent, ret);

	return ret; 
}

bool Player::Eat(const Item& item)
{
	//Todo 
	return false; 
}

bool Player::Loot(const Item& item)
{
	//Todo
	return false;
}

bool Player::Drop(const Item& item)
{
	//Todo
	return false; 
}