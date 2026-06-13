#pragma once

#include <memory>

class SessionState;
class AuthManager;
class BattleOrchestrator;
class MenuSystem;

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