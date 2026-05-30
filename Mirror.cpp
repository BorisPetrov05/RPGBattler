#include "Mirror.h"

//Mirror: Cost 80XP, prevents opponent from using special ability

Mirror::Mirror() : Item("Mirror", 80)
{
}

void Mirror::use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext)
{
	userContext.mirrorActive = true;
}

Item* Mirror::clone() const
{
	return new Mirror(*this);
}