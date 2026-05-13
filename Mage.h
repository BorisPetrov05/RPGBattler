#pragma once
#include "Character.h"

class Mage : public Character
{
	//HP = 12
	//Damage = 1-12
	//Level = 1
	//Ability: Damage Reversal: Mage sees damage of attack, and choose to reverse it (12 becomes 0, 11 becomes 1, etc.) or not.
public:
	Mage(const MyString& name = "Mage", const CharacterType& type = CharacterType::Mage);

	virtual void UseAbility(int& damage) override;
	virtual Character* clone() const override;

};