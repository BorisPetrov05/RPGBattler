#pragma once
#include "Item.h"

class Sword : public Item
{
	//cost 50XP, double damage
public:
	Sword();
	virtual ~Sword() = default;
	void use(Character& user, Character& enemy, BattleContext& context) override;
	Item* clone() const override;
};