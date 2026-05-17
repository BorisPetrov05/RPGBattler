#include "Shield.h"

Shield::Shield() : Item("Shield", 100)
{
}

void Shield::use(Character& user, Character& enemy, BattleContext& context)
{
	context.shieldActive = true;
}

Item* Shield::clone() const
{
	return new Shield(*this);
}