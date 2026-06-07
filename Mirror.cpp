#include "Mirror.h"

//Mirror: Cost 80XP, prevents opponent from using special ability

const int COST = 80;

Mirror::Mirror() : Item("Mirror", COST)
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