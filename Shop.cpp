#include "Shop.h"
#include "User.h"

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

const int LEVEL_UP_COST = 100;
const int CHARACTER_COST = 100;

void Shop::showMenu(User& user) 
{
	int choice;

	do
	{
		std::println("\nWelcome to the Shop, {}! Your XP: {}", user.getUsername(), user.getXP());
		std::println("1. Buy Character");
		std::println("2. Buy Item");
		std::println("3. Level Up Character");
		std::println("4. Exit Shop");
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
		}
	} while (choice!=4);
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
	std::print("Enter choice: ");

	int choice;
	std::cin >> choice;

	Character* ch = nullptr;

	switch (choice)
	{
	case 1:
		ch = new Warrior("Warrior");
		break;
	case 2:
		ch = new Mage("Mage");
		break;
	case 3:
		ch = new Archer("Archer");
		break;
	case 4:
		std::println("Purchase cancelled.");
		return;
	default:
		std::println("Invalid choice! Purchase cancelled.");
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
	std::cin >> choice;

	Item* item = nullptr;
	int cost = 0;

	switch (choice)
	{
	case 1:
		item = new HealingPotion(); cost = 30;
		break;
	case 2:
		item = new Sword(); cost = 50;
		break;
	case 3:
		item = new Shield(); cost = 80;
		break;
	case 4:
		item = new Ray(); cost = 70;
		break;
	case 5:
		item = new Mirror(); cost = 100;
		break;
	case 6:
		std::println("Purchase cancelled.");
		return;
	default:
		std::println("Invalid choice! Purchase cancelled.");
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		return;
	}

	if (user.getXP() < cost)
	{
		delete item;
		std::println("Not enough XP.");
		return;
	}

	user.addItem(item);
	user.addXP(-cost);

	std::println("Item purchased successfully!");
}

void Shop::buyLevelUp(User& user)
{

	if (user.getXP() < LEVEL_UP_COST)
	{
		std::println("Not enough XP.");
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
	std::print("Enter choice: ");
	std::cin >> chIndex;

	if (chIndex == 0 || chIndex > user.getCharacterCount())
	{
		std::println("Invalid choice.");
		return;
	}

	Character* selected = user.getCharacter(chIndex - 1);

	std::println("\nUpgrade type:");
	std::println("1. Increase Max HP by 2");
	std::println("2. Increase Max Damage by 1");
	std::print("Enter choice: ");

	int upgradeChoice;
	std::cin >> upgradeChoice;

	if (upgradeChoice != 1 && upgradeChoice != 2)
	{
		std::println("Invalid choice.");
		return;
	}

	selected->levelUp(upgradeChoice - 1); //choices are 0 and 1 in levelUp function
	user.addXP(-LEVEL_UP_COST);

	std::println("Character leveled up successfully!");
}