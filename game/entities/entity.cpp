#include "../common.h"

Entity::Entity(const entType& type, const int& id, const std::string& name, const Location& location, const int& hp)
	: _type(type), _id(id), _name(name), _location(location), _hp(hp) 
{
	Log::PrintCreation<Entity>(*this);
}

int Entity::id = 0;

const Entity::entType& Entity::GetType() const { return _type; }

const int& Entity::GetId() const { return _id; }

const std::string& Entity::GetName() const { return _name; }

const bool Entity::IsAlive() const { return _isAlive; }

const Location& Entity::GetLocation() const { return _location; }

void Entity::Act() 
{
	if (!_path.empty())
	{
		Move(_path.front());
	}
}

bool Entity::operator==(const Entity& ent)
{
	if (_id == ent._id && _type == ent._type)
	{
		return true;
	}
	else
	{
		return false; 
	}
}

bool Entity::Move(Location location)
{
	Location loc = NextLocation(location);

	Grid& currentGrid = *_location.grid;

	//If location is same as current location just exit function and signal that "move" succesful. 
	if (_location == loc)
		return true; 

	bool ret;

	if (currentGrid.MoveEntity(*this, loc))
	{
		_location = loc; 

		ret = true; 
	}
	else
	{
		ret = false; 
	}

	Log::PrintAction("moving entity", *this, ret);

	return ret; 
}

//Helper function for Entity::Move. Handles path changes. 
Location Entity::NextLocation(const Location& endLoc)
{
	int cx = _location.x;
	int cy = _location.y;

	Location ret = endLoc; 

	//If location is not next to entity create new path. 
	if (!((abs(endLoc.x - cx) + abs(endLoc.y - cy)) <= 1))
	{
		_path = _location.grid->GeneratePath(_location, endLoc);

		//If path found take first location and move there else return current loc. 
		if (!_path.empty())
		{
			ret = _path.front(); 
			_path.pop();
		}
		else
		{
			ret = _location; 
		}

	}
	else
	{
		if (!_path.empty())
		{
			if (_path.front() == endLoc)
			{
				_path.pop();
			}
			else
			{
				_path = std::queue<Location>();
			}
		}
	}

	return ret; 

}

void Entity::ReduceHP(const int& amount)
{
	if (_type != Entity::entType::npc)
	{
		_hp = _hp - amount;

		if (_hp <= 0)
		{
			_isAlive = false; 
		}
	}
}

void Entity::IncreaseHP(const int& amount)
{
	if (_type != Entity::entType::npc && _isAlive)
	{
		_hp = _hp + amount;

	}
}

std::ostream& operator<<(std::ostream& os, const Entity& ent)
{
	std::string entType;

	switch (ent._type)
	{
	case Entity::entType::player:
		entType = "player";
		break;
	case Entity::entType::monster:
		entType = "monster";
		break;
	case Entity::entType::npc:
		entType = "npc";
		break;
	}

	os << entType << " " << ent._id << " " << ent._name << " " << ent._location;

	return os; 
}
