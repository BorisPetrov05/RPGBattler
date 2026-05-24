#pragma once
#include "MyString.hpp"
#include "MyVector.hpp"
#include "Item.h"

class User
{
private:
	MyString username;
	MyString password;
	int xp;
	int battlesFought;
	int battlesWon;
	MyVector<Character*> characters;
	MyVector<Item*> items;

public:
	User();
	User(const MyString& username, const MyString& password);
	User(const User& other);
	User(User&& other) noexcept;
	User& operator=(const User& other);
	User& operator=(User&& other) noexcept;
	~User();

	//Character Management
	void addCharacter(Character* character);
	void removeCharacter(size_t index);
	Character* getCharacter(size_t index) const;
	size_t getCharacterCount() const;

	//Item Management
	void addItem(Item* item);
	void removeItem(size_t index);
	Item* getItem(size_t index) const;
	size_t getItemCount() const;

	//Experience
	void addXP(int amount);
	int getXP() const;

	//Stats
	void incrementBattlesFought();
	void incrementBattlesWon();
	int getBattlesFought() const;
	int getBattlesWon() const;
	double getWinRate() const;

	const MyString& getUsername() const;
	const MyString& getPassword() const;
	bool checkPassword(const MyString& password) const;

	void printProfile() const;
	void free();
	void copyFrom(const User& other);
	void moveFrom(User&& other);
 };