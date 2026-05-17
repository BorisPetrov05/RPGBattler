#pragma once
#include "Item.h"

class Mirror : public Item
{
	//cost 80XP, prevents opponent from using special ability
public:
	Mirror();
	virtual ~Mirror() = default;
	void use(Character& user, Character& enemy, BattleContext& context) override;
	Item* clone() const override;
};