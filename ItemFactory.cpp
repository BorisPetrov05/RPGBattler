#include "ItemFactory.h"
#include "HealingPotion.h"
#include "Sword.h"
#include "Shield.h"
#include "Ray.h"
#include "Mirror.h"

Item* ItemFactory::createItem(ItemType type)
{
	switch (type)
	{
	case ItemType::HealingPotion: return new HealingPotion();
	case ItemType::Sword: return new Sword();
	case ItemType::Shield: return new Shield();
	case ItemType::Ray: return new Ray();
	case ItemType::Mirror: return new Mirror();
	default: return nullptr;
	}
}

Item* ItemFactory::createItemByName(const MyString& typeName)
{
	ItemType type = stringToType(typeName);
	return createItem(type);
}

ItemType ItemFactory::stringToType(const MyString& typeName)
{
	if (typeName == "HealingPotion") return ItemType::HealingPotion;
	if (typeName == "Sword") return ItemType::Sword;
	if (typeName == "Shield") return ItemType::Shield;
	if (typeName == "Ray") return ItemType::Ray;
	if (typeName == "Mirror") return ItemType::Mirror;
	return ItemType::Unknown;
}

MyString ItemFactory::typeToString(ItemType type)
{
	switch (type)
	{
	case ItemType::HealingPotion: return MyString("HealingPotion");
	case ItemType::Sword: return MyString("Sword");
	case ItemType::Shield: return MyString("Shield");
	case ItemType::Ray: return MyString("Ray");
	case ItemType::Mirror: return MyString("Mirror");
	default: return MyString("Unknown");
	}
}
