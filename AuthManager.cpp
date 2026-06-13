#include "AuthManager.h"
#include "SessionState.h"
#include "FileManager.h"

#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "HealingPotion.h"
#include "Sword.h"
#include "Mirror.h"
#include "Ray.h"
#include "Shield.h"

#include <iostream>
#include <print>

const int BUFFER_SIZE = 256;

AuthManager::AuthManager(SessionState& sessionState) : session(sessionState)
{
}

Character* AuthManager::createCharacter(int choice, const MyString& name) const
{
	switch (choice)
	{
	case 1:
		return new Warrior(name);
	case 2:
		return new Mage(name);
	case 3:
		return new Archer(name);
	default:
		return nullptr;
	}
}

Item* AuthManager::createItem(int choice) const
{
	switch (choice)
	{
	case 1:
		return new HealingPotion();
	case 2:
		return new Sword();
	case 3:
		return new Shield();
	case 4:
		return new Ray();
	case 5:
		return new Mirror();
	default:
		return nullptr;
	}
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
	newUser->addXP(100); //Starting XP

	std::println("Account created.");
	std::println("Choose a free character:");
	std::println("1. Warrior");
	std::println("2. Mage");
	std::println("3. Archer");
	std::println("4. Skip");

	int charChoice = 0;
	std::cin >> charChoice;

	if (charChoice >= 1 && charChoice <= 3)
	{
		std::cout << "Enter character name: ";
		std::cin >> buffer;

		MyString charName = buffer;
		Character* ch = createCharacter(charChoice, charName);

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
	std::cin >> itemChoice;

	Item* item = createItem(itemChoice);
	if (item)
	{
		newUser->addItem(item);
		std::println("Free item added.");
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
