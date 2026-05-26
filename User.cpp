#include "User.h"
#include <iostream>

//helper functions
void User::free()
{
	for (size_t i = 0; i < characters.size(); i++)
	{
		delete characters[i];
	}
	characters.clear();

	for (size_t i = 0; i < items.size(); i++)
	{
		delete items[i];
	}
	items.clear();
}

void User::copyFrom(const User& other)
{
	username = other.username;
	password = other.password;
	xp = other.xp;
	battlesFought = other.battlesFought;
	battlesWon = other.battlesWon;
	//Deep copy of characters and items
	for (size_t i = 0; i < other.characters.size(); i++)
	{
		characters.push_back(other.characters[i]->clone());
	}
	for (size_t i = 0; i < other.items.size(); i++)
	{
		items.push_back(other.items[i]->clone());
	}
}

void User::moveFrom(User&& other)
{
	username = std::move(other.username);
	password = std::move(other.password);

	xp = other.xp;
	battlesFought = other.battlesFought;
	battlesWon = other.battlesWon;

	characters = std::move(other.characters);
	items = std::move(other.items);

	other.xp = 0;
	other.battlesFought = 0;
	other.battlesWon = 0;
}

//Constructors and Destructor
User::User()
	: username(""), password(""), xp(0), battlesFought(0), battlesWon(0)
{
}

User::User(const MyString& username, const MyString& password)
	: username(username), password(password), xp(0), battlesFought(0), battlesWon(0)
{
}

User::User(const User& other)
{
	copyFrom(other);
}

User::User(User&& other) noexcept
{
	moveFrom(std::move(other));
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

User& User::operator=(User&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

User::~User()
{
	free();
}

//Character Management
void User::addCharacter(Character* character)
{
	characters.push_back(character);
}

void User::removeCharacter(size_t index)
{
	if (index >= characters.size()) return;

	delete characters[index];
	//characters.erase(index);
	for (size_t i = index; i < characters.size()-1; i++)
	{
		characters[i] = characters[i + 1];
	}
	characters.pop_back();
}

Character* User::getCharacter(size_t index) const
{
	if (index >= characters.size()) return nullptr;
	return characters[index];
}

size_t User::getCharacterCount() const
{
	return characters.size();
}

//Item Management

void User::addItem(Item* item)
{
	items.push_back(item);
}

void User::removeItem(size_t index)
{
	if (index >= items.size()) return;
	delete items[index];
	//items.erase(index);
	for (size_t i = index; i < items.size() - 1; i++)
	{
		items[i] = items[i + 1];
	}
	items.pop_back();
}

Item* User::getItem(size_t index) const
{
	if (index >= items.size()) return nullptr;
	return items[index];
}

size_t User::getItemCount() const
{
	return items.size();
}

//Experience

void User::addXP(int amount)
{
	xp += amount;
}

int User::getXP() const
{
	return xp;
}

//Stats

void User::incrementBattlesFought()
{
	battlesFought++;
}

void User::incrementBattlesWon()
{
	battlesWon++;
}

int User::getBattlesFought() const
{
	return battlesFought;
}

int User::getBattlesWon() const
{
	return battlesWon;
}

double User::getWinRate() const
{
	if (battlesFought == 0)
	{
		return 0.0;
	}

	return static_cast<double>(battlesWon) / battlesFought;
}

const MyString& User::getUsername() const
{
	return username;
}

const MyString& User::getPassword() const
{
	return password;
}

bool User::checkPassword(const MyString& password) const
{
	return this->password == password;
}

void User::printProfile() const
{
	std::cout << "=== User Profile ===" << std::endl;
	std::cout << "Username: " << username.c_str() << std::endl;
	std::cout << "XP: " << xp << std::endl;
	std::cout << "Battles Fought: " << battlesFought << std::endl;
	std::cout << "Battles Won: " << battlesWon << std::endl;
	std::cout << "Win Rate: " << (getWinRate() * 100) << "%" << std::endl;

	std::cout << "\n--- Characters (" << characters.size() << ") ---" << std::endl;
	if (characters.empty()) {
		std::cout << "No characters yet." << std::endl;
	} else {
		for (std::size_t i = 0; i < characters.size(); ++i) {
			Character* ch = characters[i];
			std::cout << "[" << (i + 1) << "] " << ch->getName().c_str() 
					  << " (Lvl " << ch->getLevel() << ") - " 
					  << ch->getTypeName().c_str() 
					  << " | HP: " << ch->getCurrentHP() << "/" << ch->getMaxHP() << std::endl;
		}
	}

	std::cout << "\n--- Items (" << items.size() << ") ---" << std::endl;
	if (items.empty()) {
		std::cout << "No items yet." << std::endl;
	} else {
		for (std::size_t i = 0; i < items.size(); ++i) {
			Item* item = items[i];
			std::cout << "[" << (i + 1) << "] " << item->getName().c_str() 
					  << " (" << item->getTypeName().c_str() << ") - Cost: " 
					  << item->getCost() << std::endl;
		}
	}

	std::cout << "===================" << std::endl;
}