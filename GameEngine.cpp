#include "GameEngine.h"

#include <iostream>
#include <print>

#include "Battle.h"
#include "FileManager.h"
#include "Leaderboard.h"
#include "Shop.h"

GameEngine::GameEngine()
{
    loadUsers();
}

GameEngine::~GameEngine()
{
    saveUsers();

    for (size_t i = 0; i < users.size(); i++)
        delete users[i];
}

void GameEngine::loadUsers()
{
    users = FileManager::loadUsers();

    MyString username;
    MyString character;

    if (FileManager::loadState(username, character))
    {
        currentUser = findUser(username);
    }
}

void GameEngine::saveUsers() const
{
    FileManager::saveUsers(users);

    if (currentUser)
        FileManager::saveState(currentUser->getUsername(), "");
    else
        FileManager::saveState("", "");
}

User* GameEngine::findUser(const MyString& username) const
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i]->getUsername() == username)
            return users[i];
    }

    return nullptr;
}

void GameEngine::registerUser()
{
    MyString username;
    MyString password;

    char buffer[256];

    std::cout << "Username: ";
    std::cin >> buffer;
    username = buffer;

    if (findUser(username))
    {
        std::println("User already exists!");
        return;
    }

    std::cout << "Password: ";
    std::cin >> buffer;
    password = buffer;

	User* newUser = new User(username, password);
	newUser->addXP(100); //Starting XP for new users
    users.push_back(newUser);
    //todo: give free character and free item

    std::println("Account created.");
}

void GameEngine::login()
{
    char usernameBuffer[256];
    char passwordBuffer[256];

    std::cout << "Username: ";
    std::cin >> usernameBuffer;

    User* user = findUser(usernameBuffer);

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

    currentUser = user;
    MyString currentUsername = currentUser->getUsername();

    std::println("Logged in as {}", currentUsername.c_str());
}

Character* GameEngine::chooseCharacter(User* user) const
{
    if (!user || user->getCharacterCount() == 0)
        return nullptr;

    std::println("Choose character:");

    for (size_t i = 0; i < user->getCharacterCount(); i++)
    {
        Character* ch = user->getCharacter(i);

        std::println("{}: {} ({})",
            i + 1,
            ch->getName().c_str(),
            ch->getTypeName().c_str());
    }

    size_t choice;
    std::cin >> choice;

    if (choice >= 1 || choice <= user->getCharacterCount())
        return user->getCharacter(choice - 1);

    return nullptr;

}

void GameEngine::battleMenu()
{
    if (users.size() < 2)
    {
        std::println("Not enough players.");
        return;
    }

    std::println("Choose opponent:");

    size_t shownIndex = 1;

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i] == currentUser)
            continue;

        std::println("{}: {}", shownIndex++, users[i]->getUsername().c_str());
    }

    size_t choice;
    std::cin >> choice;

    User* opponent = nullptr;

    size_t current = 1;

    for (size_t i = 0; i < users.size(); i++)
    {
        if (users[i] == currentUser)
            continue;

        if (current == choice)
        {
            opponent = users[i];
            break;
        }

        current++;
    }

    if (!opponent)
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

    saveUsers();
}

void GameEngine::logout()
{
    std::println("Logged out.");
    currentUser = nullptr;
}

void GameEngine::profileMenu() const
{
	//bug: if you input string, the menu will break, to be fixed.
	if (!currentUser)
		return;

	while (true)
	{
		currentUser->printProfile();

		std::println("\n1. Edit Character");
		std::println("2. Buy Character");
		std::println("3. Buy Item");
		std::println("4. Back");

		int choice;
		if (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::println("Invalid input! Please enter a number.");
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			std::println("Choose character to level up:");
			Character* ch = chooseCharacter(currentUser);
			if (ch)
			{
				std::println("1. Increase Max HP");
				std::println("2. Increase Damage");
				std::println("3. Cancel");
				int levelChoice;
				if (!(std::cin >> levelChoice))
				{
					std::cin.clear();
					std::cin.ignore(10000, '\n');
					std::println("Upgrade cancelled.");
					break;
				}
				if (levelChoice == 1 || levelChoice == 2)
				{
					ch->levelUp(levelChoice);
					std::println("Character upgraded!");
				}
				else
				{
					std::println("Upgrade cancelled.");
				}
			}
			break;
		}

		case 2:
		{
			Shop shop;
			shop.buyCharacter(*const_cast<User*>(currentUser));
			break;
		}

		case 3:
		{
			Shop shop;
			shop.buyItem(*const_cast<User*>(currentUser));
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

void GameEngine::leaderboardMenu() const
{
    Leaderboard leaderboard;
    leaderboard.update(const_cast<MyVector<User*>&>(users));
    leaderboard.sort();
    leaderboard.display();
}

void GameEngine::userMenu()
{
    while (currentUser)
    {
        std::println("\n=== USER MENU ===");
        std::println("1. Profile");
        std::println("2. Battle");
        std::println("3. Shop");
        std::println("4. Leaderboard");
        std::println("5. Logout");

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            profileMenu();
            break;

        case 2:
            battleMenu();
            break;

        case 3:
        {
            Shop shop;
            shop.showMenu(*currentUser);
            break;
        }

        case 4:
            leaderboardMenu();
            break;

        case 5:
            logout();
            return;

        default:
            std::println("Invalid choice! Please try again.");
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }

    }
}

void GameEngine::mainMenu()
{
    while (!currentUser)
    {
        std::println("\n=== RPG BATTLER ===");
        std::println("1. Register");
        std::println("2. Login");
        std::println("3. Exit");

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            registerUser();
            break;

        case 2:
            login();
            break;

        case 3:
            saveUsers();
            exit(0);

        default:
			std::println("Invalid choice! Please try again.");
			std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }
    }
}

void GameEngine::run()
{
    while (true)
    {
        if (!currentUser)
            mainMenu();
        else
            userMenu();
    }
}
