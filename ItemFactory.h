#pragma once

#include "MyString.hpp"
#include "Item.h"

enum class ItemType
{
	HealingPotion,
	Sword,
	Shield,
	Ray,
	Mirror,
	Unknown
};

class ItemFactory
{
public:
	static Item* createItem(ItemType type);

	static Item* createItemByName(const MyString& typeName);

	static ItemType stringToType(const MyString& typeName);

	static MyString typeToString(ItemType type);

};
