#pragma once

#include "../common.h"

//Non agressive character that wanders around the map. 
class Npc : public Entity
{
public:

	Npc(const std::string& name, const Location& location);

	//Npc cannot perform these so calling will just return false.
	bool Attack(Entity&);
	bool Eat(const Item&);

	void Act();

};