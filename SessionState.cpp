#include "SessionState.h"
#include "FileManager.h"

SessionState::SessionState()
{
	loadUsers();
}

SessionState::~SessionState()
{
	cleanup();
}

void SessionState::addUser(User* user)
{
	if (user) users.push_back(user);
}

User* SessionState::findUser(const MyString& username) const
{
	for (size_t i = 0; i < users.size(); ++i)
	{
		if (users[i]->getUsername() == username) return users[i];
	}
	return nullptr;
}

const MyVector<User*>& SessionState::getUsers() const
{
	return users;
}

MyVector<User*>& SessionState::getMutableUsers()
{
	return users;
}

User* SessionState::getCurrentUser() const
{
	return currentUser;
}

void SessionState::setCurrentUser(User* user)
{
	currentUser = user;
}

void SessionState::clearCurrentUser()
{
	currentUser = nullptr;
}

void SessionState::loadUsers()
{
	users = FileManager::loadUsers();

	MyString username;
	MyString character;

	if (FileManager::loadState(username, character))
	{
		currentUser = findUser(username);
	}
}

void SessionState::saveUsers() const
{
	FileManager::saveUsers(users);

	if (currentUser)
		FileManager::saveState(currentUser->getUsername(), "");
	else
		FileManager::saveState("", "");
}

void SessionState::cleanup()
{
	for (size_t i = 0; i < users.size(); ++i) delete users[i];
}
