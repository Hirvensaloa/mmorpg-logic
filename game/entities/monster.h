#pragma once

#include "../common.h"

//Entity sub-class, is hostile to player. 
class Monster : public Entity
{
public:

	Monster(const std::string& name, const Location& location, const uint32_t dmg, const int& hp);

	void Act();

	bool Attack(Entity&);

	//Monster cannot perform these actions so just return false.
	bool Eat(const Item&);

private:

	uint32_t _dmg;
};
