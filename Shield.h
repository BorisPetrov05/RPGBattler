#pragma once
#include "Item.h"

class Shield : public Item
{
public:
	Shield();
	virtual ~Shield() = default;
	void use(Character& user, Character& enemy, BattleContext& context) override;
	Item* clone() const override;
};