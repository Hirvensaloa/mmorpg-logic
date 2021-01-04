#pragma once

#include "../common.h"

//Players have inventory which contains items. Inventory can contain maximum of 24 items. 
class Inventory
{
	public:

		Inventory();

		//Adds item to inventory, returns true if succeeded or false otherwise
		bool AddItem(const std::shared_ptr<Item>& item);

		bool RemoveItem(const std::shared_ptr<Item>& item);

		//Checks if inventory contains item. 
		bool ContainsItem(const std::shared_ptr<Item>& item);

	private:

		std::vector<std::shared_ptr<Item>> _items;

};