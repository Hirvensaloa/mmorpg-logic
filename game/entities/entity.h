#pragma once

#include "../common.h"

//Abstract class for all non-playable entities in the game (npcs and monsters). 
class Entity : public std::enable_shared_from_this<Entity>
{

public:

	enum class entType
	{
		player,
		monster,
		npc
	};

	static int id;

	Entity(const entType& type, const int& id, const std::string& name, const Location& location, const int& hp = 100);

	const Entity::entType& GetType() const;
	const int& GetId() const;
	const std::string& GetName() const;
	const bool IsAlive() const;

	//Moves entity to coordinates, returns true if succesful and false otherwise.
	bool Move(Location location);
	
	//Other action methods. 
	virtual bool Attack(Entity&) = 0;
	virtual bool Eat(const Item&) = 0;

	//Called when its entitys turn to act. On default checks whether player is currently moving into location.
	virtual void Act();

	//Method for reducing and increasing entitys hp.
	void ReduceHP(const int& amount);
	void IncreaseHP(const int& amount);

	const Location& GetLocation() const;

	bool operator==(const Entity& ent);
	friend std::ostream& operator<<(std::ostream& os, const Entity& ent);

protected:

	Entity::entType _type;
	int _id; 
	std::string _name;
	Location _location;
	int _hp;

	//If player is travelling the path is stored here.
	std::queue<Location> _path; 

	//Tells whether entity is alive or not. 
	bool _isAlive = true; 

	//Helper function for moving. 
	Location NextLocation(const Location& endLoc);

};