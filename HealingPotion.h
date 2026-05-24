#pragma once
#include "Item.h"

class HealingPotion : public Item
{
	//Cost: 30XP, Heal 5-10
public:
	HealingPotion();
	virtual ~HealingPotion() = default;
	void use(Character& user, Character& enemy, BattleContext& context) override;
	Item* clone() const override;
	MyString getTypeName() const override { return "Healing Potion"; }
};