#include "FileManager.h"

#include <fstream>

#include "Character.h"
#include "Item.h"

#include "CharacterFactory.h"
#include "ItemFactory.h"

const char* FileManager::USERS_FILE = "users.dat";
const char* FileManager::STATE_FILE = "state.dat";

void FileManager::saveString(std::ofstream& out, const MyString& str)
{
	size_t length = str.length();
	out.write(reinterpret_cast<const char*>(&length), sizeof(length));
	out.write(str.c_str(), length);
}

void FileManager::saveState(const MyString& activeUsername, const MyString& activeCharacter)
{
	std::ofstream ofs(STATE_FILE, std::ios::binary);
	if (!ofs.is_open()) return;

	saveString(ofs, activeUsername);
	saveString(ofs, activeCharacter);

	ofs.close();
}

bool FileManager::loadState(MyString& activeUsername, MyString& activeCharacter)
{
	std::ifstream ifs(STATE_FILE, std::ios::binary);
	if (!ifs.is_open()) return false;

	loadString(ifs, activeUsername);
	loadString(ifs, activeCharacter);
	ifs.close();

	return true;
	//function has security issues, if the file is edited manually, you can log into another user's account by changing the username in the file.
	//To be fixed.
}

void FileManager::loadString(std::ifstream& in, MyString& str)
{
	size_t length;
	in.read(reinterpret_cast<char*>(&length), sizeof(length));

	char* buffer = new char[length + 1];
	in.read(buffer, length);
	buffer[length] = '\0';
	str = MyString(buffer);

	delete[] buffer;
}

void FileManager::saveUser(std::ofstream& out, const User& user)
{
	saveString(out, user.getUsername());
	saveString(out, user.getPassword());

	int xp = user.getXP();
	int battlesFought = user.getBattlesFought();
	int battlesWon = user.getBattlesWon();

	out.write(reinterpret_cast<const char*>(&xp), sizeof(xp));
	out.write(reinterpret_cast<const char*>(&battlesFought), sizeof(battlesFought));
	out.write(reinterpret_cast<const char*>(&battlesWon), sizeof(battlesWon));

	size_t characterCount = user.getCharacterCount();
	out.write(reinterpret_cast<const char*>(&characterCount), sizeof(characterCount));

	for (size_t i = 0; i < characterCount; i++)
	{
		saveCharacter(out, user.getCharacter(i));
	}

	size_t itemCount = user.getItemCount();
	out.write(reinterpret_cast<const char*>(&itemCount), sizeof(itemCount));

	for (size_t i = 0; i < itemCount; i++)
	{
		saveItem(out, user.getItem(i));
	}
}

User* FileManager::loadUser(std::ifstream& in)
{
	MyString username;
	MyString password;

	loadString(in, username);
	loadString(in, password);

	User* user = new User(username, password);

	int xp;
	int battlesFought;
	int battlesWon;

	in.read(reinterpret_cast<char*>(&xp), sizeof(xp));
	in.read(reinterpret_cast<char*>(&battlesFought), sizeof(battlesFought));
	in.read(reinterpret_cast<char*>(&battlesWon), sizeof(battlesWon));

	user->addXP(xp);

	for (int i = 0; i < battlesFought; i++) user->incrementBattlesFought();

	for (int i = 0; i < battlesWon; i++) user->incrementBattlesWon();

	size_t characterCount;
	in.read(reinterpret_cast<char*>(&characterCount), sizeof(characterCount));

	for (size_t i = 0; i < characterCount; i++)
	{
		Character* character = loadCharacter(in);
		if(character) user->addCharacter(character);
	}
	size_t itemCount;
	in.read(reinterpret_cast<char*>(&itemCount), sizeof(itemCount));

	for (size_t i = 0; i < itemCount; i++)
	{
		Item* item = loadItem(in);
		if(item) user->addItem(item);
	}

	return user;
}

void FileManager::saveCharacter(std::ofstream& out, const Character* character)
{
	saveString(out, character->getTypeName());
	saveString(out, character->getName());

	int level = character->getLevel();
	int maxHP = character->getMaxHP();
	int currentHP = character->getCurrentHP();
	int minDamage = character->getMinDamage();
	int maxDamage = character->getMaxDamage();

	out.write(reinterpret_cast<const char*>(&level), sizeof(level));
	out.write(reinterpret_cast<const char*>(&maxHP), sizeof(maxHP));
	out.write(reinterpret_cast<const char*>(&currentHP), sizeof(currentHP));
	out.write(reinterpret_cast<const char*>(&minDamage), sizeof(minDamage));
	out.write(reinterpret_cast<const char*>(&maxDamage), sizeof(maxDamage));
}

Character* FileManager::loadCharacter(std::ifstream& in)
{
	MyString type;
	MyString name;

	loadString(in, type);
	loadString(in, name);

	int level;
	int maxHP;
	int currentHP;
	int minDamage;
	int maxDamage;

	in.read(reinterpret_cast<char*>(&level), sizeof(level));
	in.read(reinterpret_cast<char*>(&maxHP), sizeof(maxHP));
	in.read(reinterpret_cast<char*>(&currentHP), sizeof(currentHP));
	in.read(reinterpret_cast<char*>(&minDamage), sizeof(minDamage));
	in.read(reinterpret_cast<char*>(&maxDamage), sizeof(maxDamage));

	Character* character = CharacterFactory::createCharacterByName(type, name);

	if (!character)
	{
		return nullptr;
	}

	character->setLevel(level);
	character->setMaxHP(maxHP);
	character->setCurrentHP(currentHP);
	character->setMinDamage(minDamage);
	character->setMaxDamage(maxDamage);

	return character;
}

void FileManager::saveItem(std::ofstream& ofs, const Item* item)
{
	saveString(ofs, item->getTypeName());
}

Item* FileManager::loadItem(std::ifstream& ifs)
{
	MyString type;
	loadString(ifs, type);

	return ItemFactory::createItemByName(type);
}


void FileManager::saveUsers(const MyVector<User*>& users)
{
	std::ofstream ofs(USERS_FILE, std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}

	size_t count = users.size();
	ofs.write(reinterpret_cast<const char*>(&count), sizeof(count));

	for (size_t i = 0; i < users.size(); i++)
	{
		saveUser(ofs, *users[i]);
	}

	ofs.close();
}

MyVector<User*> FileManager::loadUsers()
{
	MyVector<User*> users;

	std::ifstream ifs(USERS_FILE, std::ios::binary);

	if (!ifs.is_open())
	{
		return users;
	}

	size_t count;
	ifs.read(reinterpret_cast<char*>(&count), sizeof(count));

	for (size_t i = 0; i < count; i++)
	{
		User* user = loadUser(ifs);

		if (user)
		{
			users.push_back(user);
		}
	}

	ifs.close();

	return users;
}