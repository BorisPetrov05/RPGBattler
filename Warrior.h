#pragma once
#include "Character.h"

class Warrior : public Character
{
	//HP = 20
	//Damage = 1-8
	//Level = 1
	//Ability: Reduces damage by a random value between 1 and 4.
public:
	Warrior(const MyString& name);

	virtual void UseAbility(int& damage) override;
	virtual Character* clone() const override;
	virtual MyString getTypeName() const override { return "Warrior"; }

};