#pragma once
#include "MyString.hpp"
#include "Character.h"
#include "BattleContext.h"

class Item 
{
private:
	MyString name;
	int cost;

public:
	Item(const MyString& name, int cost);
	virtual ~Item() = default;

	virtual void use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext) = 0;
	virtual Item* clone() const = 0;
	const MyString& getName() const;
	int getCost() const;
	virtual MyString getTypeName() const = 0;

};