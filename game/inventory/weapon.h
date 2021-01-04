#pragma once

#include "../common.h"

class Weapon : public Item
{
	public:

		Weapon(const std::string& name, const int value, const int damage);

		bool Action(const ActionType&, Entity&);

	private:

		int _damage; 
};