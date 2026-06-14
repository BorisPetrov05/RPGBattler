#pragma once

#include "SessionState.h"

class AuthManager
{
private:
	SessionState& session;

public:
	AuthManager(SessionState& sessionState);

	void registerUser();

	void login();

	void logout();
};
