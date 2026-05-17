#include "Sword.h"

Sword::Sword() : Item("Sword", 50)
{
}

void Sword::use(Character& user, Character& enemy, BattleContext& context)
{
	context.swordActive = true;
}

Item* Sword::clone() const
{
	return new Sword(*this);
}