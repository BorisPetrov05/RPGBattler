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

public:
	Battle(User* player1, User* player2);

	void start();
	void chooseCharacters();
	void performTurn();
	void attack(Character* attacker, Character* defender);
	void useItem(User& user, Character& userCharacter, Character& enemyCharacter);
	bool isBattleOver() const;
	User* getWinner() const;
	void awardXP(User* winner, User* loser);
	void resetCharacters();

};