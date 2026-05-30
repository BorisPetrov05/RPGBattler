#include "Archer.h"
#include <print>
#include <iostream>

//Archer: HP = 15, Damage = 1-8, Level = 1 default, Ability: Double Damage

Archer::Archer(const MyString& name) : Character(name, CharacterType::Archer, 15, 1, 8)
{

}

void Archer::UseAbility(int& damage)
{
	if (damage < 1 || damage > 4)
	{
		return;
	}

	std::println("You rolled {} damage.", damage);
	std::println("Use Double Damage ability? (y/n)");

	char choice;
	std::cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		damage *= 2;
		std::println("Doubled damage: {}", damage);
	}
}

Character* Archer::clone() const
{
	return new Archer(*this);
}