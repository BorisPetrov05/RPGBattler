#pragma once
#include "Item.h"

class Ray : public Item
{
	//cost 70XP, cancels mirror
public:
	Ray();
	virtual ~Ray() = default;
	void use(Character& user, Character& enemy, BattleContext& context) override;
	Item* clone() const override;
	MyString getTypeName() const override { return "Ray"; }
};