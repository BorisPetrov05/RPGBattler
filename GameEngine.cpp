#include "GameEngine.h"

#include <iostream>
#include <print>

#include "Battle.h"
#include "FileManager.h"
#include "Leaderboard.h"
#include "Shop.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "HealingPotion.h"
#include "Sword.h"
#include "Mirror.h"
#include "Ray.h"
#include "Shield.h"

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

    // Offer a free character
    std::println("Account created.");
    std::println("Choose a free character:");
    std::println("1. Warrior");
    std::println("2. Mage");
    std::println("3. Archer");
    std::println("4. Skip");
    int choice = 0;
    std::cin >> choice;
    if (choice >= 1 && choice <= 3)
    {
        std::cout << "Enter character name: ";
        std::cin >> buffer;
        MyString cname = buffer;
        Character* ch = nullptr;
        if (choice == 1) ch = new Warrior(cname);
        else if (choice == 2) ch = new Mage(cname);
        else if (choice == 3) ch = new Archer(cname);

        if (ch)
        {
            newUser->addCharacter(ch);
            std::println("Free character added: {}", cname.c_str());
        }
    }

    // Offer a free item
    std::println("Choose a free item:");
    std::println("1. HealingPotion");
    std::println("2. Sword");
    std::println("3. Shield");
    std::println("4. Ray");
    std::println("5. Mirror");
    std::println("6. Skip");
    int c = 0;
    std::cin >> c;
    Item* it = nullptr;
    switch (c)
    {
    case 1: it = new HealingPotion(); break;
    case 2: it = new Sword(); break;
    case 3: it = new Shield(); break;
    case 4: it = new Ray(); break;
    case 5: it = new Mirror(); break;
    default: break;
    }
    if (it)
    {
        newUser->addItem(it);
        std::println("Free item added.\n");
    }

	std::println("Registration successful! You can now log in.");
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

    std::println("{}, Choose character:", user->getUsername().c_str());

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
    {
        std::println("Invalid opponent selection.");
        return;
    }

    //Require the opponent to authenticate before the battle
    {
        const int MAX_ATTEMPTS = 3;
        bool authenticated = false;
        char enteredUser[256];
        char enteredPass[256];

        for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++)
        {
            std::println("{}, please enter your credentials to start the battle (attempt {}/{})", opponent->getUsername().c_str(), attempt, MAX_ATTEMPTS);
            std::cout << "Username: ";
            std::cin >> enteredUser;
            std::cout << "Password: ";
            std::cin >> enteredPass;

            MyString enteredUsername = enteredUser;
            if (enteredUsername == opponent->getUsername() && opponent->checkPassword(enteredPass))
            {
                authenticated = true;
                break;
            }
            else
            {
                std::println("Authentication failed.");
            }
        }

        if (!authenticated)
        {
            std::println("Opponent failed to authenticate. Cancelling battle.");
            return;
        }
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
			std::print("Renaming a character... ");
            MyString name;
			Character* ch = chooseCharacter(currentUser);
            std::print("Enter character name: ");
            std::cin >> name;
			ch->setName(name);
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
