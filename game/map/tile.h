#pragma once

#include "../common.h"

//Tile can be accessible or inaccessible, if accessible it can have items and entities. 
class Tile
{
public:

	Tile(bool IsAccessible, const Location& location);

	const std::list<std::shared_ptr<Entity>>& GetEntities() const;
	Entity& GetEntity(const int& id); 
	const Location& GetLocation() const; 

	bool isAccessible() const;
 
	bool AddEntity(const std::shared_ptr<Entity> ent);
	void RemoveEntity(const std::shared_ptr<Entity>& ent);
	bool ContainsEntity(const Entity& ent) const;
	bool ContainsPlayer() const; 

	bool AddItem(const std::shared_ptr<Item>& item);
	bool ContainsItem(const Item& item) const;

	//Removes certain item. 
	bool RemoveItem(const Item& item);

	//Removes all nullptr items. 
	void RemoveItems();

	friend std::ostream& operator<<(std::ostream& os, const Tile& tile);

	void GetState(std::ostream& os) const;

private:

	bool _isAccessible;
	Location _location; 

	std::list<std::shared_ptr<Entity>> _entities;
	std::list<std::shared_ptr<Item>> _items;
};