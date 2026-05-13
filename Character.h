#pragma once
#include "MyString.hpp"

enum class CharacterType
{
	Warrior,
	Mage,
	Archer
};

class Character
{
private:
	MyString name;
	CharacterType type;

	int maxHP;
	int currentHP;

	int level = 1;

	int minDamage;
	int maxDamage;

public:
	Character();
	Character(const MyString& name, CharacterType type, int maxHP, int level, int minDamage, int maxDamage);
	Character(const Character& other);
	Character(Character&& other) noexcept;

	int attack() const;
	void takeDamage(int amount);
	void heal(int amount);
	void resetHP();
	bool isAlive() const;
	void levelUp(int choice);
	void UseAbility() const;
	void clone() const;

	MyString getName() const;
	CharacterType getType() const;
	int getMaxHP() const;
	int getCurrentHP() const;
	int getLevel() const;
	int getMinDamage() const;
	int getMaxDamage() const;

};