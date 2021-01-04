#pragma once

#include "../common.h"

class Food : public Item
{
	public:

		Food(const std::string name, const int value, const int heal);

		bool Action(const ActionType& action, Entity& caller);

	private:

		int _heal; 
};
