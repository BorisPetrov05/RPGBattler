#pragma once

#include "MyString.hpp"

class User;
class Character;
class SessionState;

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
