#include "../common.h"

Weapon::Weapon(const std::string& name, const int value, const int damage)
	: Item(ItemType::weapon, name, value), _damage(damage) {}

bool Weapon::Action(const ActionType&, Entity&)
{
	//Todo
	return false; 
}