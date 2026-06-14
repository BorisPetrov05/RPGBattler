#include "AuthManager.h"
#include "SessionState.h"
#include "CharacterFactory.h"
#include "ItemFactory.h"

#include <iostream>
#include <print>

const int STARTING_XP = 100;
const int CHARACTER_COST = 100;
const int BUFFER_SIZE = 256;

AuthManager::AuthManager(SessionState& sessionState) : session(sessionState)
{
}

void AuthManager::registerUser()
{
	MyString username;
	MyString password;
	char buffer[BUFFER_SIZE];

	std::cout << "Username: ";
	std::cin >> buffer;
	username = buffer;

	if (session.findUser(username))
	{
		std::println("User already exists!");
		return;
	}

	std::cout << "Password: ";
	std::cin >> buffer;
	password = buffer;

	User* newUser = new User(username, password);
	newUser->addXP(STARTING_XP); //Starting XP

	std::println("Account created.");
	std::println("Choose a free character:");
	std::println("1. Warrior");
	std::println("2. Mage");
	std::println("3. Archer");
	std::println("4. Skip");

	int charChoice = 0;
	std::print("> ");
	std::cin >> charChoice;

	if (charChoice >= 1 && charChoice <= 3)
	{
		std::cout << "Enter character name: ";
		std::cin >> buffer;
		MyString charName = buffer;

		CharacterType type = static_cast<CharacterType>(charChoice - 1);
		Character* ch = CharacterFactory::createCharacter(type, charName);

		if (ch)
		{
			newUser->addCharacter(ch);
			std::println("Free character added: {}", charName.c_str());
		}
	}

	std::println("Choose a free item:");
	std::println("1. HealingPotion");
	std::println("2. Sword");
	std::println("3. Shield");
	std::println("4. Ray");
	std::println("5. Mirror");
	std::println("6. Skip");

	int itemChoice = 0;
	std::print("> ");
	std::cin >> itemChoice;

	if (itemChoice >= 1 && itemChoice <= 5)
	{
		ItemType type = static_cast<ItemType>(itemChoice - 1);
		Item* item = ItemFactory::createItem(type);
		if (item)
		{
			newUser->addItem(item);
			std::println("Free item added.");
		}
	}

	session.addUser(newUser);
	std::println("Registration successful! You can now log in.");
}

void AuthManager::login()
{
	char usernameBuffer[BUFFER_SIZE];
	char passwordBuffer[BUFFER_SIZE];

	std::cout << "Username: ";
	std::cin >> usernameBuffer;

	User* user = session.findUser(usernameBuffer);

	if (!user)
	{
		std::println("User not found.");
		return;
	}

	std::cout << "Password: ";
	std::cin >> passwordBuffer;

	if (!user->checkPassword(passwordBuffer))
	{
		std::println("Wrong password.");
		return;
	}

	session.setCurrentUser(user);
	std::println("Logged in as {}", user->getUsername().c_str());
}

void AuthManager::logout()
{
	std::println("Logged out.");
	session.clearCurrentUser();
}
