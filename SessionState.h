#pragma once

#include "MyVector.hpp"
#include "User.h"

class SessionState
{
private:
	MyVector<User*> users;
	User* currentUser = nullptr;

public:
	SessionState();
	~SessionState();

	void addUser(User* user);
	User* findUser(const MyString& username) const;
	const MyVector<User*>& getUsers() const;
	MyVector<User*>& getMutableUsers();

	User* getCurrentUser() const;
	void setCurrentUser(User* user);
	void clearCurrentUser();

	void loadUsers();
	void saveUsers() const;
	void cleanup();
};
