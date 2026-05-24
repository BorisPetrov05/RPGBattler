#pragma once
#include "Item.h"

class Mirror : public Item
{
	//cost 80XP, prevents opponent from using special ability
public:
	Mirror();
	virtual ~Mirror() = default;
	void use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext) override;
	Item* clone() const override;
	MyString getTypeName() const override { return "Mirror"; }
};