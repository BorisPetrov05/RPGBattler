#pragma once

#include "User.h"
#include "Character.h"
#include "SessionState.h"
#include "AuthManager.h"
#include "BattleOrchestrator.h"

class MenuSystem
{
private:
	SessionState& session;
	AuthManager& authManager;
	BattleOrchestrator& battleOrchestrator;
	bool shouldExit = false;

	void displayMainMenu() const;
	void displayUserMenu() const;
	void displayProfileMenu() const;

	//Sub-menu handlers
	void handleProfileMenu() const;
	void handleShopMenu() const;
	void handleLeaderboard() const;
	void handleExitGame();

	//Input helpers
	int getMenuChoice() const;
	Character* getCharacterSelectionFromUser(User* user) const;

public:
	MenuSystem(SessionState& sessionState, AuthManager& authMgr, BattleOrchestrator& battleOrch);

	//Before login
	void mainMenuLoop();

	//After login
	void userMenuLoop();

	bool shouldExitGame() const;
};
