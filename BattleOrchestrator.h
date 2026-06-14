#pragma once

#include "User.h"
#include "Character.h"
#include "SessionState.h"

class BattleOrchestrator
{
private:
	SessionState& session;

	User* selectOpponent() const;

	bool authenticateOpponent(User* opponent) const;

	Character* chooseCharacter(User* user) const;

public:
	BattleOrchestrator(SessionState& sessionState);

	void startBattle();
};
