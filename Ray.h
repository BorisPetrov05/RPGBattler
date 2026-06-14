#pragma once
#include "Item.h"

class Ray : public Item
{
	//cost 70XP, cancels mirror, doesnt consume turn
public:
	Ray();

	virtual ~Ray() = default;

	void use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext) override;

	Item* clone() const override;

	MyString getTypeName() const override { return "Ray"; }

	bool consumesTurn() const override { return false; }

};