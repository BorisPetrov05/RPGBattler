#pragma once

#include <fstream>

#include "MyString.hpp"
#include "MyVector.hpp"
#include "User.h"

class FileManager
{
private:
	static const char* USERS_FILE;
	static const char* STATE_FILE;

	static void saveString(std::ofstream& out, const MyString& str);
	static void loadString(std::ifstream& in, MyString& str);

	static void saveUser(std::ofstream& out, const User& user);
	static User* loadUser(std::ifstream& in);

	static void saveCharacter(std::ofstream& out, const Character* character);
	static Character* loadCharacter(std::ifstream& in);

	static void saveItem(std::ofstream& out, const Item* item);
	static Item* loadItem(std::ifstream& in);

public:
	static void saveUsers(const MyVector<User*>& users);
	static MyVector<User*> loadUsers();

	static void saveState(const MyString& activeUsername, const MyString& activeCharacter);
	static bool loadState(MyString& activeUsername, MyString& activeCharacter);
};