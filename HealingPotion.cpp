#include "HealingPotion.h"
#include <cstdlib>
#include <print>

//Healing Potion: Cost 30XP, Heal 5-10 HP

const int COST = 30;

HealingPotion::HealingPotion() : Item("Healing Potion", COST)
{
}

void HealingPotion::use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext)
{
	int healAmount = rand() % 6 + 5; // Heal 5-10
	user.heal(healAmount);
	std::println("{} uses {} and heals for {} HP!", user.getName(), getName(), healAmount);
}

Item* HealingPotion::clone() const
{
	return new HealingPotion(*this);
}