#pragma once
#include "Item.h"

class Shield : public Item
{
public:
	Shield();
	virtual ~Shield() = default;
	void use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext) override;
	Item* clone() const override;
	MyString getTypeName() const override { return "Shield"; }
};