#include "Shield.h"

//Shield: Cost 100XP, reduces damage from opponent's next attack by half

Shield::Shield() : Item("Shield", 100)
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