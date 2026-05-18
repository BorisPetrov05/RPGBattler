#pragma once
#include "User.h"

class Shop
{
public:
	void buyCharacter(User& user);
	void buyItem(User& user);
	void buyLevelUp(User& user);

	void showMenu(User& user);

};