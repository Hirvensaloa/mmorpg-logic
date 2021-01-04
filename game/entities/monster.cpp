#include <stdlib.h>
#include <algorithm>
#include "../common.h"

Monster::Monster(const std::string& name, const Location& location, const uint32_t dmg, const int& hp)
	: Entity(Entity::entType::monster, id++, name, location, hp), _dmg(dmg) {}

bool Monster::Eat(const Item&) { return false; }

void Monster::Act()
{

	std::vector<Tile> neighbours = _location.grid->Neighbours(_location.x, _location.y);

	//Tries to find players nearby.
	auto it = std::find_if(neighbours.begin(), neighbours.end(),
		[](const Tile& tile)
		{
			return tile.ContainsPlayer();
		}
	);

	//If player found, attack else move or do nothing.
	if (0 && it != neighbours.end())  //TODO! Monster cant attack at the moment because server cannot handle dying. 
	{
		const std::list<std::shared_ptr<Entity>>& entities = (*it).GetEntities();

		auto entIt = find_if(entities.begin(), entities.end(),
			[](const std::shared_ptr<Entity>& ent)
			{
				return ent->GetType() == Entity::entType::player; 
			}
			);

		std::shared_ptr<Entity> target = *entIt;

		Attack(*target);
		
	}
	else
	{
		const unsigned int randy = rand() % 15;

		if (randy == 0)
		{
			
			auto it = neighbours.begin();

			unsigned int randy1 = rand() % neighbours.size();

			while (it != neighbours.end())
			{

				if ((*it).isAccessible() && !randy1)
				{
					Move((*it).GetLocation()); 
					break;
				}

				randy1--;
				it++;
			}

		}
	}
}


bool Monster::Attack(Entity& ent)
{
	bool ret; 

	//Attack only if entity is false and is not type npc. 
	if (ent.GetType() != Entity::entType::npc && ent.IsAlive())
	{

		//Random number between 0 and maximum damage monster can deal. 
		const unsigned int damage = rand() % _dmg;

		ent.ReduceHP(damage);

		ret = true;

	}
	else
	{
		ret = false; 
	}

	Log::PrintAction("attack by monster " + GetId(), ent, ret);

	return ret; 
}