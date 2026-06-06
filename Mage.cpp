#include "Mage.h"
#include <print>
#include <iostream>

Mage::Mage(const MyString& name) : Character(name, CharacterType::Mage, 12, 1, 12)
{
}

//Ability: Damage Reversal: Mage sees damage of attack, and choose to reverse it (12 becomes 0, 11 becomes 1, etc.) or not.
void Mage::UseAbility(int& damage)
{
	if (damage < 1 || damage > 12) //with sword, damage can be over 12 here, intended, levelup doesn't increase range for ability, intended
	{
		//output maybe
		return;
	}
	std::println("You rolled {} damage.", damage);
	std::println("Use Damage Reversal ability? (y/n)");
	char choice;
	std::cin >> choice;
	if (choice == 'y' || choice == 'Y')
	{
		damage = 12 - damage; //Reverse damage
		std::println("Reversed damage: {}", damage);
	}
}

Character* Mage::clone() const
{
	return new Mage(*this);
}