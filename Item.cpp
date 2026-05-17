#include "Item.h"

Item::Item(const MyString& name, int cost) : name(name), cost(cost)
{
}

void Item::use(Character& user, Character& enemy, BattleContext& context)
{
	//do nothing
}

const MyString& Item::getName() const
{
	return name;
}

int Item::getCost() const
{
	return cost;
}