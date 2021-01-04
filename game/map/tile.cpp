#include <algorithm>
#include "../common.h"

Tile::Tile(bool IsAccessible, const Location& location)
	: _isAccessible(IsAccessible), _location(location) {}

const std::list<std::shared_ptr<Entity>>& Tile::GetEntities() const { return _entities; }

bool Tile::isAccessible() const { return _isAccessible; }

const Location& Tile::GetLocation() const { return _location; }; 

Entity& Tile::GetEntity(const int& id)
{
	auto it = _entities.begin();

	while (it != _entities.end())
	{
		if ((*it)->GetId() == id)
		{
			break; 
		}
	}

	return *(*it);
}

bool Tile::AddEntity(const std::shared_ptr<Entity> ent)
{
	if (_isAccessible && !ContainsEntity(*ent))
	{
		_entities.push_back(ent);
 
		return true;
	}
	else
	{
		return false;
	}
}

void Tile::RemoveEntity(const std::shared_ptr<Entity>& ent)
{
	auto it = std::find(_entities.begin(), _entities.end(), ent);

	if (it != _entities.end())
	{
		_entities.erase(it);
	}
}

bool Tile::ContainsEntity(const Entity& ent) const
{
	auto it = std::find_if(_entities.begin(), _entities.end(), 
		[&](const std::shared_ptr<Entity>& cmp)
		{
			return *cmp == ent;
		}
	);

	if (it == _entities.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Tile::AddItem(const std::shared_ptr<Item>& item)
{
	if (_isAccessible && !ContainsItem(*item))
	{
		_items.push_back(item);

		return true;
	}
	else
	{
		return false;
	}
}

bool Tile::RemoveItem(const Item& item)
{
	auto it = std::find_if(_items.begin(), _items.end(),
		[&](const std::shared_ptr<Item>& cmp)
		{
			return *cmp == item; 
		}
	);

	if (it != _items.end())
	{
		_items.erase(it);

		return true; 
	}
	else
	{
		return false; 
	}
}

bool Tile::ContainsItem(const Item& item) const
{
	auto it = std::find_if(_items.begin(), _items.end(),
		[&](const std::shared_ptr<Item>& cmp)
		{
			return *cmp == item;
		}
	);

	if (it == _items.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Tile::ContainsPlayer() const
{
	
	auto it = find_if(_entities.cbegin(), _entities.cend(),
		[](const std::shared_ptr<Entity>& ent)
		{
			return ent->GetType() == Entity::entType::player;
		});

	if (it != _entities.cend())
	{
		return true;
	}
	else
	{
		return false; 
	}

}

void Tile::RemoveItems()
{
	auto it = _items.cbegin();

	while (it != _items.cend())
	{
		if (*it == nullptr)
		{
			_items.erase(it);
		}
		else
		{
			it++;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Tile& tile)
{
	os << "Tile " << tile.GetLocation(); 

	return os; 
}

void Tile::GetState(std::ostream& os) const
{
	os << *this << " entities: ";

	auto it = _entities.cbegin();

	while (it != _entities.cend())
	{
		os << *(*it) << " | ";

		it++;
	}

	os << "\nand items:";

	auto iter = _items.cbegin();

	while (iter != _items.cend())
	{
		os << *iter << " | ";

		iter++; 
	}
}
