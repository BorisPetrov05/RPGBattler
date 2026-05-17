#pragma once
#include "User.h"

class Leaderboard
{
private:
	MyVector <User*> users;

	bool shouldComeBefore(const User* lhs, const User* rhs) const;
public:
	void sort();
	void update(MyVector<User*>& allUsers);
	void display() const;
};