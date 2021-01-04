#pragma once

#include "../common.h"

class Entity;

class Item
{
	public:

		//Types of action that can be performed for an item or atleast try to perform. 
		enum class ActionType
		{
			wear,
			eat,
			wield
		};

		//Types of items. 
		enum class ItemType
		{
			food,
			armour,
			weapon
		};

		static int id; 

		Item(const ItemType& type, const std::string& name, const int value);

		//Entities can call action on items. Action have different outcomes depending on the type of child item. 
		virtual bool Action(const ActionType&, Entity&) = 0;

		const ItemType& GetType() const;
		const int& GetId() const;

		friend std::ostream& operator<<(std::ostream& os, const Item& item);

		bool operator==(const Item& item);

	protected:

		ItemType _type; 
		std::string _name;
		int _value; 
		int _id; 
};