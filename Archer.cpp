#include "Archer.h"
#include <print>
#include <iostream>

//Archer: HP = 15, Damage = 1-8, Level = 1 default, Ability: Double Damage

const int ARCHER_HP = 15;
const int MIN_DAMAGE = 1;
const int MAX_DAMAGE = 8;

Archer::Archer(const MyString& name) : Character(name, CharacterType::Archer, ARCHER_HP, MIN_DAMAGE, MAX_DAMAGE)
{

}

void Archer::UseAbility(int& damage)
{
	if (damage < 1 || damage > 4) //sword can increase damage above 4, intended, levelup doesn't increase range for ability, intended
	{
		std::println("Damage is too high for Double Damage ability!");
		return;
	}

	std::println("You rolled {} damage.", damage);
	std::println("Use Double Damage ability? (y/n)");
	std::print("> ");

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