#pragma once
#include "Item.h"

class Shield : public Item
{
	//Cost 100XP, reduces damage by half, doesnt consume turn
public:
	Shield();

	virtual ~Shield() = default;

	void use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext) override;

	Item* clone() const override;

	MyString getTypeName() const override { return "Shield"; }

	bool consumesTurn() const override { return false; }
};