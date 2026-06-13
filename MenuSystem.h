#pragma once

class User;
class Character;
class SessionState;
class AuthManager;
class BattleOrchestrator;

class MenuSystem
{
private:
	SessionState& session;
	AuthManager& authManager;
	BattleOrchestrator& battleOrchestrator;
	bool shouldExit = false;

	//Menu displays and input handling
	void displayMainMenu() const;
	void displayUserMenu() const;
	void displayProfileMenu() const;

	//Sub-menu handlers
	void handleProfileMenu() const;
	void handleShopMenu() const;
	void handleLeaderboard() const;

	//Input helpers
	int getMenuChoice() const;
	Character* getCharacterSelectionFromUser(User* user) const;

public:
	MenuSystem(SessionState& sessionState, AuthManager& authMgr, BattleOrchestrator& battleOrch);

	//Before login
	void mainMenuLoop();

	//After login
	void userMenuLoop();

	//Check if user requested exit
	bool shouldExitGame() const;
};
