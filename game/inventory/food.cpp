#include "../common.h"

Food::Food(const std::string name, const int value, const int heal)
	: Item(ItemType::food, name, value), _heal(heal) {}

bool Food::Action(const ActionType& action, Entity& caller)
{
	if (action == ActionType::eat)
	{
		caller.IncreaseHP(_heal);

		return true;
	}
	else
	{
		return false;
	}
}