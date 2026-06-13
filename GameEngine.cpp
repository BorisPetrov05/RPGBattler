#include "GameEngine.h"
#include "SessionState.h"
#include "AuthManager.h"
#include "BattleOrchestrator.h"
#include "MenuSystem.h"

#include <iostream>

GameEngine::GameEngine()
{
	initializeComponents();
}

GameEngine::~GameEngine()
{
	//Cleanup happens automatically with unique_ptr destruction
}

void GameEngine::initializeComponents()
{
	//Create session (loads users from disk)
	session = std::make_unique<SessionState>();

	//Create managers with session dependency injection
	authManager = std::make_unique<AuthManager>(*session);
	battleOrchestrator = std::make_unique<BattleOrchestrator>(*session);

	//Create menu system with all dependencies
	menuSystem = std::make_unique<MenuSystem>(*session, *authManager, *battleOrchestrator);
}

void GameEngine::run()
{
	while (true)
	{
		if (!session->getCurrentUser())
		{
			menuSystem->mainMenuLoop();
		}
		else
		{
			menuSystem->userMenuLoop();
		}
	}
}
