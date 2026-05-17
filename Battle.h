#pragma once
#include "User.h"

class Battle
{
private:
	User* player1;
	User* player2;
	Character* character1;
	Character* character2;
	int currentTurn;

	BattleContext context1;
	BattleContext context2;

public:
	Battle(User* player1, User* player2);

	void chooseCharacters();
	void attack(Character* attacker, Character* defender);
	void performTurn();
	void useItem(User& user, Character& userCharacter, Character& enemyCharacter);
	bool isBattleOver() const;
	User* getWinner() const;
	void awardXP(User* winner, User* loser);
	void resetCharacters();
	void start();

};