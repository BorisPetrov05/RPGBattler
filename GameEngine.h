#pragma once

#include "MyVector.hpp"
#include "User.h"

class GameEngine
{
private:
    MyVector<User*> users;
    User* currentUser = nullptr;

    void loadUsers();
    void saveUsers() const;

    User* findUser(const MyString& username) const;

    void mainMenu();
    void userMenu();

    void registerUser();
    void login();
    void logout();

    void battleMenu();
    void leaderboardMenu() const;
    void profileMenu() const;

    Character* chooseCharacter(User* user) const;

public:
    GameEngine();
    ~GameEngine();

    void run();
};