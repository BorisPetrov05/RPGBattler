#include "BattleOrchestrator.h"
#include "SessionState.h"
#include "Battle.h"

#include <iostream>
#include <print>

static const int MAX_OPPONENT_AUTH_ATTEMPTS = 3;
static const int BUFFER_SIZE = 256;

BattleOrchestrator::BattleOrchestrator(SessionState& sessionState) : session(sessionState)
{
}

User* BattleOrchestrator::selectOpponent() const
{
	User* currentUser = session.getCurrentUser();
	const MyVector<User*>& users = session.getUsers();

	if (users.size() < 2)
	{
		std::println("Not enough players for battle.");
		return nullptr;
	}

	std::println("Choose opponent:");

	size_t shownIndex = 1;
	for (size_t i = 0; i < users.size(); ++i)
	{
		if (users[i] != currentUser)
		{
			std::println("{}: {}", shownIndex++, users[i]->getUsername().c_str());
		}
	}

	size_t choice = 0;
	std::cin >> choice;

	size_t current = 1;
	for (size_t i = 0; i < users.size(); ++i)
	{
		if (users[i] == currentUser)
			continue;

		if (current == choice)
			return users[i];

		current++;
	}

	std::println("Invalid opponent selection.");
	return nullptr;
}

bool BattleOrchestrator::authenticateOpponent(User* opponent) const
{
	if (!opponent)
		return false;

	char enteredUser[BUFFER_SIZE];
	char enteredPass[BUFFER_SIZE];

	for (int attempt = 1; attempt <= MAX_OPPONENT_AUTH_ATTEMPTS; ++attempt)
	{
		std::println("{}, please enter your credentials to start the battle (attempt {}/{})",
					 opponent->getUsername().c_str(), attempt, MAX_OPPONENT_AUTH_ATTEMPTS);
		std::cout << "Username: ";
		std::cin >> enteredUser;
		std::cout << "Password: ";
		std::cin >> enteredPass;

		MyString enteredUsername = enteredUser;
		if (enteredUsername == opponent->getUsername() && opponent->checkPassword(enteredPass))
		{
			return true;
		}
		else
		{
			std::println("Authentication failed.");
		}
	}

	std::println("Opponent failed to authenticate. Cancelling battle.");
	return false;
}

Character* BattleOrchestrator::chooseCharacter(User* user) const
{
	if (!user || user->getCharacterCount() == 0)
		return nullptr;

	std::println("{}, choose character:", user->getUsername().c_str());

	for (size_t i = 0; i < user->getCharacterCount(); ++i)
	{
		Character* ch = user->getCharacter(i);
		std::println("{}: {} ({})", i + 1, ch->getName().c_str(), ch->getTypeName().c_str());
		//[number]: [character name] ([character type])
	}

	size_t choice = 0;
	std::cin >> choice;

	if (choice >= 1 && choice <= user->getCharacterCount())
		return user->getCharacter(choice - 1);

	return nullptr;
}

void BattleOrchestrator::startBattle()
{
	User* currentUser = session.getCurrentUser();
	if (!currentUser)
	{
		std::println("You must be logged in to battle.");
		return;
	}

	User* opponent = selectOpponent();
	if (!opponent)
		return;

	if (!authenticateOpponent(opponent))
		return;

	Character* myChar = chooseCharacter(currentUser);
	Character* enemyChar = chooseCharacter(opponent);

	if (!myChar || !enemyChar)
	{
		std::println("Character selection failed.");
		return;
	}

	Battle battle(currentUser, opponent);
	battle.setCharacters(myChar, enemyChar);
	battle.start();

	session.saveUsers();
}
