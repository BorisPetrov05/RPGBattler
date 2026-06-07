#include "Sword.h"

//Sword: Cost 50XP, double damage for next attack

const int COST = 50;

Sword::Sword() : Item("Sword", COST)
{
}

void Sword::use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext)
{
	userContext.swordActive = true;
}

Item* Sword::clone() const
{
	return new Sword(*this);
}