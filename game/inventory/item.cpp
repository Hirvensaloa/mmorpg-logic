#include "../common.h"

Item::Item(const ItemType& type, const std::string& name, const int value)
	: _type(type), _name(name), _value(value), _id(id++)
{
	Log::PrintCreation<Item>(*this);
}

int Item::id = 0; 

const Item::ItemType& Item::GetType() const { return _type; } 

const int& Item::GetId() const { return _id; }

bool Item::operator==(const Item& item)
{
	if (_id == item._id)
		return true;
	else
		return false; 
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << item._name << " value " << item._value;

	return os;
}