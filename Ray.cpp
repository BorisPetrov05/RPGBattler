#include "Ray.h"

Ray::Ray() : Item("Ray", 70)
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