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
	Character(const MyString& name, int maxHP, int minDamage, int maxDamage, int level = 1);
	virtual ~Character() = default;

	virtual int attack() const;
	void takeDamage(int amount);
	void heal(int amount);
	void resetHP();
	bool isAlive() const;
	void levelUp(int choice);
	virtual void UseAbility(int& damage);
	virtual Character* clone() const = 0;

	const MyString& getName() const;
	CharacterType getType() const;
	int getMaxHP() const;
	int getCurrentHP() const;
	int getLevel() const;
	int getMinDamage() const;
	int getMaxDamage() const;
	virtual MyString getTypeName() const = 0;

	void setLevel(int level);
	void setMaxHP(int maxHP);
	void setCurrentHP(int currentHP);
	void setMinDamage(int minDamage);
	void setMaxDamage(int maxDamage);
};