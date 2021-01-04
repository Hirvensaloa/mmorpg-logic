#include <stdlib.h>
#include "../common.h"

Npc::Npc(const std::string& name, const Location& location)
	: Entity(Entity::entType::npc, id++, name, location) {}

void Npc::Act()
{
	const unsigned int randy = rand() % 15;

	if (randy == 0)
	{

		std::vector<Tile> neighbours = _location.grid->Neighbours(_location.x, _location.y);

		auto it = neighbours.begin();

		unsigned int randy1 = rand() % neighbours.size();

		while (it != neighbours.end())
		{
			if ((*it).isAccessible() && !randy1)
			{
				Move((*it).GetLocation());
				return;
			}

			randy1--;
			it++;
		}

	}
}

bool Npc::Attack(Entity&)
{
	return false; 
}

bool Npc::Eat(const Item&)
{
	return false; 
}