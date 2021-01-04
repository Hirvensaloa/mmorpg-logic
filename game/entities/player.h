#pragma once

#include "../common.h"

//Represents a player. Player is entitys sub-class. 
class Player : public Entity
{

public:

	Player(const int& id, const std::string& name, Location& location, const Skills& skills, const Inventory& inventory);

	bool Attack(Entity& ent);
	bool Eat(const Item& item);
	bool Loot(const Item& item);
	bool Drop(const Item& item);

private:

	Skills _skills;
	Inventory _inventory;
};