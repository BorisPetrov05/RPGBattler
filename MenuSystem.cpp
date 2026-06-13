#include "MenuSystem.h"
#include "SessionState.h"
#include "AuthManager.h"
#include "BattleOrchestrator.h"
#include "User.h"
#include "Shop.h"
#include "Leaderboard.h"

#include <iostream>
#include <print>

const int BUFFER_SIZE = 256;

MenuSystem::MenuSystem(SessionState& sessionState, AuthManager& authMgr, BattleOrchestrator& battleOrch)
	: session(sessionState), authManager(authMgr), battleOrchestrator(battleOrch)
{
}

void MenuSystem::displayMainMenu() const
{
	std::println("\n=== RPG BATTLER ===");
	std::println("1. Register");
	std::println("2. Login");
	std::println("3. Exit");
}

void MenuSystem::displayUserMenu() const
{
	std::println("\n=== USER MENU ===");
	std::println("1. Profile");
	std::println("2. Battle");
	std::println("3. Shop");
	std::println("4. Leaderboard");
	std::println("5. Exit Game");
	std::println("6. Logout");
}

void MenuSystem::displayProfileMenu() const
{
	User* currentUser = session.getCurrentUser();
	if (!currentUser)
		return;

	currentUser->printProfile();
	std::println("\n1. Edit Character");
	std::println("2. Buy Character");
	std::println("3. Buy Item");
	std::println("4. Back");
}

int MenuSystem::getMenuChoice() const
{
	int choice = 0;
	if (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return -1; //Invalid
	}
	return choice;
}

Character* MenuSystem::getCharacterSelectionFromUser(User* user) const
{
	if (!user || user->getCharacterCount() == 0)
		return nullptr;

	std::println("{}, choose character:", user->getUsername().c_str());

	for (size_t i = 0; i < user->getCharacterCount(); ++i)
	{
		Character* ch = user->getCharacter(i);
		std::println("{}: {} ({})", i + 1, ch->getName().c_str(), ch->getTypeName().c_str());
	}

	size_t choice = 0;
	std::cin >> choice;

	if (choice >= 1 && choice <= user->getCharacterCount())
	{
		return user->getCharacter(choice - 1);
	}

	return nullptr;
}

void MenuSystem::handleProfileMenu() const
{
	User* currentUser = session.getCurrentUser();
	if (!currentUser)
		return;

	while (true)
	{
		displayProfileMenu();

		int choice = getMenuChoice();

		switch (choice)
		{
		case 1:
		{
			if (currentUser->getCharacterCount() == 0)
			{
				std::println("No characters available to edit.");
				break;
			}

			std::println("Choose character to rename:");
			for (size_t i = 0; i < currentUser->getCharacterCount(); ++i)
			{
				Character* ch = currentUser->getCharacter(i);
				std::println("{}: {} ({})", i + 1, ch->getName().c_str(), ch->getTypeName().c_str());
			}

			size_t chIndex = 0;
			std::cout << "Enter choice: ";
			if (!(std::cin >> chIndex) || chIndex == 0 || chIndex > currentUser->getCharacterCount())
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::println("Invalid choice.");
				break;
			}

			char nameBuf[BUFFER_SIZE];
			std::cout << "Enter new name: ";
			std::cin >> nameBuf;
			MyString newName = nameBuf;
			currentUser->getCharacter(chIndex - 1)->setName(newName);
			std::println("Character renamed to {}", newName.c_str());
			break;
		}

		case 2:
		{
			Shop shop;
			shop.buyCharacter(*currentUser);
			break;
		}

		case 3:
		{
			Shop shop;
			shop.buyItem(*currentUser);
			break;
		}

		case 4:
			return;

		default:
			std::println("Invalid choice! Please try again.");
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			break;
		}
	}
}

void MenuSystem::handleShopMenu() const
{
	User* currentUser = session.getCurrentUser();
	if (!currentUser)
		return;

	Shop shop;
	shop.showMenu(*currentUser);
}

void MenuSystem::handleLeaderboard() const
{
	Leaderboard leaderboard;
	MyVector<User*>& users = session.getMutableUsers();
	leaderboard.update(users);
	leaderboard.sort();
	leaderboard.display();
}

void MenuSystem::handleExitGame() const
{
	std::println("Are you sure you want to exit the game? (y/n)");

	char confirm = 0;
	std::cin >> confirm;

	if (confirm == 'Y' || confirm == 'y')
	{
		session.saveUsers();
		std::println("Exiting game. Your progress has been saved.");
		exit(0);
	}
	else
	{
		std::println("Exit cancelled. Returning to user menu.");
	}
}

void MenuSystem::mainMenuLoop()
{
	while (!session.getCurrentUser())
	{
		displayMainMenu();

		int choice = getMenuChoice();

		switch (choice)
		{
		case 1:
			authManager.registerUser();
			break;

		case 2:
			authManager.login();
			break;

		case 3:
			session.saveUsers();
			std::println("Goodbye!");
			exit(0);

		default:
			std::println("Invalid choice! Please try again.");
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			break;
		}
	}
}

void MenuSystem::userMenuLoop()
{
	while (session.getCurrentUser())
	{
		displayUserMenu();

		int choice = getMenuChoice();

		switch (choice)
		{
		case 1:
			handleProfileMenu();
			break;

		case 2:
			battleOrchestrator.startBattle();
			break;

		case 3:
			handleShopMenu();
			break;

		case 4:
			handleLeaderboard();
			break;

		case 5:
			handleExitGame();
			break;

		case 6:
			authManager.logout();
			return;

		default:
			std::println("Invalid choice! Please try again.");
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			break;
		}
	}
}
