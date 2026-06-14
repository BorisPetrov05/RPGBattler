#pragma once
#include "Item.h"

class Sword : public Item
{
	//cost 50XP, double damage
public:
	Sword();

	virtual ~Sword() = default;

	void use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext) override;

	Item* clone() const override;

	MyString getTypeName() const override { return "Sword"; }

};