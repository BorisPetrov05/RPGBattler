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

	//Validate username
	while (true)
	{
		std::print("Username: ");
		std::cin >> buffer;
		username = buffer;

		if (!User::isValidUsername(username))
		{
			std::println("Username must be {}-{} characters.", 
				MIN_USERNAME_LENGTH, MAX_USERNAME_LENGTH);
			continue;
		}

		if (session.findUser(username))
		{
			std::println("User already exists!");
			continue;
		}

		break;
	}

	//Validate password
	while (true)
	{
		std::print("Password: ");
		std::cin >> buffer;
		password = buffer;

		if (!User::isValidPassword(password))
		{
			std::println("Password must be {}-{} characters.", 
				MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
			continue;
		}

		break;
	}

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
	if (!(std::cin >> charChoice))
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		charChoice = 0;
	}

	if (charChoice >= 1 && charChoice <= 3)
	{
		std::cout << "Enter character name: ";
		std::cin >> buffer;
		MyString charName = buffer;

		if (charName.length() == 0 || charName.length() > 50)
		{
			std::println("Invalid character name.");
		}
		else
		{
			CharacterType type = static_cast<CharacterType>(charChoice - 1);
			Character* ch = CharacterFactory::createCharacter(type, charName);

			if (ch)
			{
				newUser->addCharacter(ch);
				std::println("Free character added: {}", charName.c_str());
			}
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
	if (!(std::cin >> itemChoice))
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		itemChoice = 0;
	}

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

	if (newUser->getCharacterCount() == 0)
	{
		std::println("No character chosen. Adding default Warrior.");
		newUser->addCharacter(CharacterFactory::createCharacter(CharacterType::Warrior, "Warrior"));
	}
	if (newUser->getItemCount() == 0)
	{
		std::println("No item chosen. Adding default Healing Potion.");
		newUser->addItem(ItemFactory::createItem(ItemType::HealingPotion));
	}

	session.addUser(newUser);
	std::println("Registration successful! You can now log in.");
}

void AuthManager::login()
{
	char usernameBuffer[BUFFER_SIZE];
	char passwordBuffer[BUFFER_SIZE];

	std::print("Username: ");
	std::cin >> usernameBuffer;

	MyString inputUsername = usernameBuffer;
	if (!User::isValidUsername(inputUsername))
	{
		std::println("Invalid username format.");
		return;
	}

	User* user = session.findUser(inputUsername);

	if (!user)
	{
		std::println("User not found.");
		return;
	}

	std::print("Password: ");
	std::cin >> passwordBuffer;

	if (!User::isValidPassword(passwordBuffer))
	{
		std::println("Invalid password format.");
		return;
	}

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
