#include "Ray.h"

//Ray: Cost 70XP, cancels mirror

const int COST = 70;

Ray::Ray() : Item("Ray", COST)
{
}

void Ray::use(Character& user, Character& enemy, BattleContext& userContext, BattleContext& enemyContext)
{
	enemyContext.mirrorActive = false;
}

Item* Ray::clone() const
{
	return new Ray(*this);
}