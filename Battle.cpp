#include "Battle.h"
#include <iostream>
#include <print>
#include "Shield.h"
#include "Ray.h"
//unfinished, Ability usage is not well implemented, weak polymorphism
Battle::Battle(User* player1, User* player2) : player1(player1), player2(player2), character1(nullptr), character2(nullptr), currentTurn(rand() % 2)
{
}

void Battle::setCharacters(Character* first, Character* second)
{
	character1 = first;
	character2 = second;
}

void Battle::attack(Character* attacker, Character* defender)
{
	BattleContext& attackerContext =
		(attacker == character1) ? context1 : context2;

	BattleContext& defenderContext =
		(defender == character1) ? context1 : context2;

	int damage = attacker->attack();

	if (defenderContext.shieldActive)
	{
		std::println("{} blocked the attack with Shield!", defender->getName());

		defenderContext.shieldActive = false;

		return;
	}

	bool abilityBlocked = defenderContext.mirrorActive && !attackerContext.rayActive;

	if(!abilityBlocked)
	{
		if (attackerContext.rayActive)
		{
			std::println("Ray blocked the mirror!");
			attackerContext.rayActive = false;
		}

		if (attackerContext.swordActive)
		{
			damage *= 2;
			attackerContext.swordActive = false;
		}

		bool abilityBlocked =
			defenderContext.mirrorActive &&
			!attackerContext.rayActive;

		if (!abilityBlocked)
		{
			if (defender->getType() == CharacterType::Warrior)
			{
				defender->UseAbility(damage);
			}
			else
			{
				attacker->UseAbility(damage);
			}
		}
		else
		{
			std::println("Mirror blocked the special ability!");
			defenderContext.mirrorActive = false;
		}

		defender->takeDamage(damage);
	}
	else
	{
		std::println("Mirror blocked the special ability!");
		defenderContext.mirrorActive = false;

	}

	std::println("{} attacks {} for {} damage!", attacker->getName(), defender->getName(), damage);
	if (!defender->isAlive())
	{
		std::println("{} has been defeated!", defender->getName());
	}
}

void Battle::performTurn()
{
	User* currentPlayer;
	Character* currentCharacter;
	Character* enemyCharacter;

	if (currentTurn % 2 == 0)
	{
		currentPlayer = player1;
		currentCharacter = character1;
		enemyCharacter = character2;
	}
	else
	{
		currentPlayer = player2;
		currentCharacter = character2;
		enemyCharacter = character1;
	}

	std::println("{}'s turn:", currentPlayer->getUsername());
	std::println("1. Attack");
	std::println("2. Use Item");

	int choice;

	while (true)
	{
		std::cout << "> ";

		if (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			continue;
		}

		if (choice == 1 || choice == 2)
			break;

		std::println("Invalid choice!");
	}

	switch (choice)
	{
	case 1:
		attack(currentCharacter, enemyCharacter);
		break;

	case 2:
		useItem(*currentPlayer, *currentCharacter, *enemyCharacter);
		break;
	}

	if (choice == 1 || lastItemConsumesTurn)
	{
		currentTurn++;
	}
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
	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		std::println("Invalid input!");
	}

	if (choice < 1 || choice > user.getItemCount())
	{
		std::println("Invalid choice!");
		return;
	}

	Item* item = user.getItem(choice - 1);
	lastItemConsumesTurn = true;

	if (dynamic_cast<Shield*>(item) ||
		dynamic_cast<Ray*>(item))
	{
		lastItemConsumesTurn = false;
	}
	BattleContext& userContext =
		(&user == player1) ? context1 : context2;

	BattleContext& enemyContext =
		(&user == player1) ? context2 : context1;

	item->use(
		userCharacter,
		enemyCharacter,
		userContext,
		enemyContext);
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
	return nullptr; //No winner yet
}

void Battle::awardXP(User* winner, User* loser)
{
	if (winner)
	{
		winner->incrementBattlesFought();
		winner->incrementBattlesWon();
		winner->addXP(10);
	}

	if (loser)
	{
		loser->incrementBattlesFought();
		loser->addXP(5);
	}
}

void Battle::resetCharacters()
{
	character1->resetHP();
	character2->resetHP();
}

void Battle::start()
{
	context1 = BattleContext{};
	context2 = BattleContext{};

	if (!character1 || !character2)
	{
		std::println("Characters not selected!");
		return;
	}
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
		std::println("The battle ended in a draw!"); //most likely wont happen but just in case
	}

	User* loser = nullptr;

	if (winner == player1)
	{
		loser = player2;
	}
	else if (winner == player2)
	{
		loser = player1;
	}

	awardXP(winner, loser);
	resetCharacters();
}