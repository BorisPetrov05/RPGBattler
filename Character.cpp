#include "Character.h"
#include <cstdlib>

//Constructors and Destructor

Character::Character(const MyString& name, CharacterType type, int maxHP, int minDamage, int maxDamage, int level)
	: name(name), type(type), maxHP(maxHP), currentHP(maxHP), minDamage(minDamage), maxDamage(maxDamage), level(level)
{
}

//Battle and HP

int Character::attack() const
{
	return minDamage + std::rand() % (maxDamage - minDamage + 1);
}

void Character::takeDamage(int amount)
{
	if (amount < 0)
	{
		amount = 0;
	}
	currentHP -= amount;
	if (currentHP < 0) currentHP = 0;
}

void Character::heal(int amount)
{
	if (amount < 0)
	{
		return;
	}

	currentHP += amount;

	if (currentHP > maxHP) currentHP = maxHP;
}

void Character::resetHP()
{
	currentHP = maxHP;
}

bool Character::isAlive() const
{
	return currentHP > 0;
}

//Outside Battle

void Character::levelUp(int choice)
{
	level++;
	
	if (choice == 0)
	{
		maxHP += 2;
		currentHP += 2;
	}
	else if (choice == 1)
	{
		maxDamage += 1;
	}
}

void Character::UseAbility(int& damage)
{
	//Do Nothing, to be derived 
}

//Getters

const MyString& Character::getName() const
{
	return name;
}

CharacterType Character::getType() const
{
	return type;
}

int Character::getMaxHP() const
{
	return maxHP;
}

int Character::getCurrentHP() const
{
	return currentHP;
}

int Character::getLevel() const
{
	return level;
}

int Character::getMinDamage() const
{
	return minDamage;
}

int Character::getMaxDamage() const
{
	return maxDamage;
}

//Setters

void Character::setLevel(int level)
{
	this->level = level;
}

void Character::setMaxHP(int maxHP)
{
	this->maxHP = maxHP;
}

void Character::setCurrentHP(int currentHP)
{
	this->currentHP = currentHP;
}

void Character::setMinDamage(int minDamage)
{
	this->minDamage = minDamage;
}

void Character::setMaxDamage(int maxDamage)
{
	this->maxDamage = maxDamage;
}

void Character::setName(const MyString& name)
{
	this->name = name;
}