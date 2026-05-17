#include "Battle.h"
#include <iostream>
#include <print>
//unfinished
Battle::Battle(User* player1, User* player2) : player1(player1), player2(player2), character1(nullptr), character2(nullptr), currentTurn(0)
{
}

void Battle::chooseCharacters()
{
	std::println("Player 1, choose your character:");
	character1 = player1->chooseCharacter();
	std::println("Player 2, choose your character:");
	character2 = player2->chooseCharacter();
}

void Battle::attack(Character* attacker, Character* defender)
{
	int damage = attacker->attack();
	if (defender->getType() == CharacterType::Warrior)
	{
		defender->UseAbility(damage);
	}
	else
	{
		attacker->UseAbility(damage);
	}
	defender->takeDamage(damage);

	std::println("{} attacks {} for {} damage!", attacker->getName(), defender->getName(), damage);
	if (!defender->isAlive())
	{
		std::println("{} has been defeated!", defender->getName());
	}
}

void Battle::performTurn()
{
	if (currentTurn % 2 == 0)
	{
		std::println("{}'s turn:", player1->getUsername());
		//todo:add menu for using item or attacking
		attack(character1, character2);
	}
	else
	{
		std::println("{}'s turn:", player2->getUsername());
		//todo:add menu for using item or attacking
		attack(character2, character1);
	}
	currentTurn++;
}

void Battle::useItem(User& user, Character& userCharacter, Character& enemyCharacter)
{
	if (user.getItemCount() == 0)
	{
		std::println("No items available!");
		return;
	}

	std::println("Choose an item to use:");
	for (size_t i = 0; i < user.getItemCount(); i++)
	{
		std::println("{}: {}", i + 1, user.getItem(i)->getName());
	}

	size_t choice;
	std::cin >> choice;
	if (choice < 1 || choice > user.getItemCount())
	{
		std::println("Invalid choice!");
		return;
	}

	Item* item = user.getItem(choice - 1);
	BattleContext& context = (&user == player1) ? context1 : context2;
	item->use(userCharacter, enemyCharacter, context);
	user.removeItem(choice - 1);
}

bool Battle::isBattleOver() const
{
	return !character1->isAlive() || !character2->isAlive();
}

User* Battle::getWinner() const
{
	if (character1->isAlive() && !character2->isAlive())
	{
		return player1;
	}
	else if (!character1->isAlive() && character2->isAlive())
	{
		return player2;
	}
	return nullptr; // No winner yet
}

void Battle::awardXP(User* winner, User* loser)
{
	if (winner)
	{
		winner->addXP(100);
		winner->incrementBattlesWon();
	}
	if (loser)
	{
		loser->addXP(50);
	}
}

void Battle::resetCharacters()
{
	character1->resetHP();
	character2->resetHP();
}

void Battle::start()
{
	chooseCharacters();
	while (!isBattleOver())
	{
		performTurn();
	}
	User* winner = getWinner();
	if (winner)
	{
		std::println("{} wins the battle!", winner->getUsername());
	}
	else
	{
		std::println("The battle ended in a draw!");
	}
	User* loser = (winner == player1) ? player2 : player1;
	awardXP(winner, loser);
	resetCharacters();
}