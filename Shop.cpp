#include "Shop.h"
#include "User.h"

#include "CharacterFactory.h"
#include "ItemFactory.h"

#include <iostream>
#include <print>

const int LEVEL_UP_COST = 100;
const int CHARACTER_COST = 100;

void Shop::showMenu(User& user) 
{
	int choice;

	do
	{
		std::println("\nWelcome to the Shop, {}! Your XP: {}", user.getUsername().c_str(), user.getXP());
		std::println("1. Buy Character (100XP)");
		std::println("2. Buy Item");
		std::println("3. Level Up Character (100XP)");
		std::println("4. Exit Shop");

		std::print("> ");
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			buyCharacter(user);
			break;
		case 2:
			buyItem(user);
			break;
		case 3:
			buyLevelUp(user);
			break;
		case 4:
			break;
		default:
			std::println("Invalid choice! Please try again.");
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	} while (choice != 4);
}

void Shop::buyCharacter(User& user)
{
	if (user.getXP() < CHARACTER_COST)
	{
		std::println("Not enough XP.");
		return;
	}

	std::println("Choose a character to buy(100XP):");
	std::println("1. Warrior");
	std::println("2. Mage");
	std::println("3. Archer");
	std::println("4. Cancel");

	int choice;
	std::print("> ");
	std::cin >> choice;

	if (choice < 1 || choice > 4)
	{
		std::println("Invalid choice! Purchase cancelled.");
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return;
	}

	if (choice == 4)
	{
		std::println("Purchase cancelled.");
		return;
	}

	MyString name;
	std::print("Enter character name: ");
	std::cin >> name;

	CharacterType type = static_cast<CharacterType>(choice - 1);
	Character* ch = CharacterFactory::createCharacter(type, name);

	if (!ch)
	{
		std::println("Character creation failed.");
		return;
	}

	user.addCharacter(ch);
	user.addXP(-CHARACTER_COST);

	std::println("Character purchased successfully!");
}

void Shop::buyItem(User& user)
{
	std::println("Choose Item:");
	std::println("1. Health Potion (30XP)");
	std::println("2. Sword (50XP)");
	std::println("3. Shield (100XP)");
	std::println("4. Ray (70 XP)");
	std::println("5. Mirror (80 XP)");
	std::println("6. Cancel");

	int choice;
	std::print("> ");
	std::cin >> choice;

	if (choice < 1 || choice > 6)
	{
		std::println("Invalid choice! Purchase cancelled.");
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return;
	}

	if (choice == 6)
	{
		std::println("Purchase cancelled.");
		return;
	}

	ItemType type = static_cast<ItemType>(choice - 1);
	Item* item = ItemFactory::createItem(type);

	if (!item)
	{
		std::println("Item creation failed.");
		return;
	}

	int currentXP = user.getXP();
	int itemCost = item->getCost();

	if (currentXP < itemCost)
	{
		delete item;
		std::println("Not enough XP.");
		return;
	}

	user.addItem(item);
	user.addXP(-itemCost);

	std::println("Item purchased successfully!");
}

void Shop::buyLevelUp(User& user)
{

	if (user.getXP() < LEVEL_UP_COST)
	{
		std::println("Not enough XP.");
		return;
	}

	if (user.getCharacterCount() == 0)
	{
		std::println("No characters available to level up.");
	}

	std::println("Choose character to level up:");

	for (size_t i = 0; i < user.getCharacterCount(); i++)
	{
		Character* ch = user.getCharacter(i);

		std::println("{}: {} (Level {})", i + 1, ch->getName().c_str(), ch->getLevel());
	}

	size_t chIndex;
	std::print("> ");
	std::cin >> chIndex;

	if (chIndex == 0 || chIndex > user.getCharacterCount())
	{
		std::println("Invalid choice.");
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return;
	}

	Character* selected = user.getCharacter(chIndex - 1);

	std::println("\nUpgrade type:");
	std::println("1. Increase Max HP by 2");
	std::println("2. Increase Max Damage by 1");

	int upgradeChoice;
	std::print("> ");
	std::cin >> upgradeChoice;

	if (upgradeChoice != 1 && upgradeChoice != 2)
	{
		std::println("Invalid choice.");
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return;
	}
	
	selected->levelUp(upgradeChoice - 1); //choices are 0 and 1 in levelUp function
	user.addXP(-LEVEL_UP_COST);

	std::println("Character leveled up successfully!");
}