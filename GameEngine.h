#pragma once

#include <memory>
#include "SessionState.h"
#include "AuthManager.h"
#include "BattleOrchestrator.h"
#include "MenuSystem.h"

class GameEngine
{
private:
    std::unique_ptr<SessionState> session;
    std::unique_ptr<AuthManager> authManager;
    std::unique_ptr<BattleOrchestrator> battleOrchestrator;
    std::unique_ptr<MenuSystem> menuSystem;

    void initializeComponents();

public:
    GameEngine();
    ~GameEngine();

    void run();
};