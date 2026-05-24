#include "GameEngine.h"
#include <iostream>

#include "FileManager.h"
#include "User.h"

void GameEngine::run() const
{
	// Load users from disk
	MyVector<User*> users = FileManager::loadUsers();

	// Restore last state if available
	MyString lastUser;
	MyString lastCharacter;
	if (FileManager::loadState(lastUser, lastCharacter))
	{
		std::cout << "Restored last session: user='" << lastUser.c_str() << "' character='" << lastCharacter.c_str() << "'\n";
	}
	else
	{
		std::cout << "No previous session found." << std::endl;
	}

	std::cout << "Running the game engine..." << std::endl;

	// TODO: present main menu / resume game logic

	// Cleanup loaded users
	for (size_t i = 0; i < users.size(); ++i)
	{
		delete users[i];
	}
}
