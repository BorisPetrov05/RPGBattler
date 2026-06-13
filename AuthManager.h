#pragma once

#include "MyString.hpp"
#include "User.h"

class SessionState;

class AuthManager
{
private:
	SessionState& session;

	Character* createCharacter(int choice, const MyString& name) const;
	Item* createItem(int choice) const;

public:
	AuthManager(SessionState& sessionState);

	void registerUser();

	void login();

	void logout();
};
