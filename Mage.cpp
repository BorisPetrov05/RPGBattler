#include "Mage.h"
#include <print>
#include <iostream>

Mage::Mage(const MyString& name) : Character(name, 12, 1, 12)
{
}

void Mage::UseAbility(int& damage)
{
	if (damage < 1 || damage > 12)
	{
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