#include "Warrior.h"
#include <cstdlib>
#include <print>

const int WARRIOR_HP = 20;
const int MIN_DAMAGE = 1;
const int MAX_DAMAGE = 8;


Warrior::Warrior(const MyString& name) : Character(name, CharacterType::Warrior, WARRIOR_HP, MIN_DAMAGE, MAX_DAMAGE)
{
}

//Ability: Reduces damage by a random value between 1 and 4.
void Warrior::UseAbility(int& damage) //automatic 
{
	int reduction = 1 + std::rand() % 4; //Random between 1 and 4
	damage -= reduction;
	if (damage < 0) damage = 0;
	std::println("Warrior's ability reduced damage by {}. Final damage: {}", reduction, damage);
}

Character* Warrior::clone() const
{
	return new Warrior(*this);
}
