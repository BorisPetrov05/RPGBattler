#include "GameEngine.h"
#include "SessionState.h"
#include "AuthManager.h"
#include "BattleOrchestrator.h"
#include "MenuSystem.h"

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
	session = std::make_unique<SessionState>();

	authManager = std::make_unique<AuthManager>(*session);
	battleOrchestrator = std::make_unique<BattleOrchestrator>(*session);

	menuSystem = std::make_unique<MenuSystem>(*session, *authManager, *battleOrchestrator);
}

void GameEngine::run()
{
	while (!menuSystem->shouldExitGame())
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
