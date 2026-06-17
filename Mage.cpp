#include "Mage.h"
#include <print>
#include <iostream>

const int MAGE_HP = 15;
const int MIN_DAMAGE = 1;
const int MAX_DAMAGE = 12;

Mage::Mage(const MyString& name) : Character(name, CharacterType::Mage, MAGE_HP, MIN_DAMAGE, MAX_DAMAGE)
{
}

//Ability: Damage Reversal: Mage sees damage of attack, and choose to reverse it (12 becomes 0, 11 becomes 1, etc.) or not.
void Mage::UseAbility(int& damage)
{
	if (damage < 1 || damage > 12) //with sword, damage can be over 12 here, intended, levelup doesn't increase range for ability, intended
	{
		std::println("Damage is too high for damage reversal!");
		return;
	}
	std::println("You rolled {} damage.", damage);
	std::println("Use Damage Reversal ability? (y/n)");
	std::print("> ");

	char choice;
	std::cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		damage = MAX_DAMAGE - damage; //Reverse damage
		std::println("Reversed damage: {}", damage);
	}
}

Character* Mage::clone() const
{
	return new Mage(*this);
}