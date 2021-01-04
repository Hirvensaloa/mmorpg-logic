#include "../common.h"

Inventory::Inventory() {}


bool Inventory::AddItem(const std::shared_ptr<Item>& item)
{
	if (_items.size() < 24 && !ContainsItem(item))
	{
		_items.push_back(item);

		return true;
	}
	else
	{
		return false;
	}
}

bool Inventory::RemoveItem(const std::shared_ptr<Item>& item)
{
	auto it = std::find(_items.cbegin(), _items.cend(), item);

	if (it != _items.cend())
	{
		_items.erase(it);

		return true;
	}
	else
	{
		return false;
	}
}

bool Inventory::ContainsItem(const std::shared_ptr<Item>& item)
{
	auto it = std::find(_items.cbegin(), _items.cend(), item);

	if (it != _items.cend())
	{
		return true; 
	}
	else
	{
		return false; 
	}
}