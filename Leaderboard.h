#pragma once
#include "User.h"

class Leaderboard
{
private:
	MyVector <User*> users;

public:
	void update(MyVector<User*>& allUsers);
	void sort();
	void display() const;
};