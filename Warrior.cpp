#include "Warrior.h"
#include <cstdlib>
#include <print>

Warrior::Warrior(const MyString& name) : Character(name, CharacterType::Warrior, 20, 1, 8)
{
}

void Warrior::UseAbility(int& damage) //automatic 
{
	int reduction = 1 + std::rand() % 4;
	damage -= reduction;
	if (damage < 0) damage = 0;
	std::println("Warrior's ability reduced damage by {}. Final damage: {}", reduction, damage);
}

Character* Warrior::clone() const
{
	return new Warrior(*this);
}