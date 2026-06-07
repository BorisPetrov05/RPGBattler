#include "Shield.h"

//Shield: Cost 100XP, reduces damage from opponent's next attack by half

const int COST = 100;

Shield::Shield() : Item("Shield", COST)
{
}

void Shield::use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext)
{
	userContext.shieldActive = true;
}

Item* Shield::clone() const
{
	return new Shield(*this);
}