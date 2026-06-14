#pragma once

class SessionState;

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
