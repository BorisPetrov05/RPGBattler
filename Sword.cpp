#include "Sword.h"

//Sword: Cost 50XP, double damage for next attack

Sword::Sword() : Item("Sword", 50)
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