#pragma once
#include "Character.h"

class Archer : public Character
{
	//HP = 15
	//Damage = 1-8
	//Level = 1
	//Ability: Double Damage: Archer can choose to double the damage of his attack if the attack damage is less than or equal to 4.
public:
	Archer(const MyString& name = "Archer", const CharacterType& type = CharacterType::Archer);

	virtual void UseAbility(int& damage) override;
	virtual Character* clone() const override;

};