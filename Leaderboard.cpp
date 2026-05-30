#include "Leaderboard.h"
#include <print>

bool Leaderboard::shouldComeBefore(const User* lhs, const User* rhs) const
{
	//More battles won first
	if (lhs->getBattlesWon() != rhs->getBattlesWon())
	{
		return lhs->getBattlesWon() > rhs->getBattlesWon();
	}

	//XP next
	if (lhs->getXP() != rhs->getXP())
	{
		return lhs->getXP() > rhs->getXP();
	}

	//win rate last
	if (lhs->getWinRate() != rhs->getWinRate())
	{
		return lhs->getWinRate() > rhs->getWinRate();
	}

	return lhs->getUsername() < rhs->getUsername();
}

//sorting users based on battles won, then XP, then win rate, then username
void Leaderboard::sort()
{
	if (users.size() < 2)
	{
		return;
	}

	for (size_t i = 0; i < users.size(); i++)
	{
		size_t bestIndex = i;

		for (size_t j = i+1; j < users.size(); j++)
		{
			if (shouldComeBefore(users[j], users[bestIndex]))
			{
				bestIndex = j;
			}
		}

		if (bestIndex != i)
		{
			User* temp = users[i];
			users[i] = users[bestIndex];
			users[bestIndex] = temp;
		}
	}
}

void Leaderboard::update(MyVector<User*>& allUsers)
{
	users = allUsers;
	sort();
}

void Leaderboard::display() const
{
	std::println("\n========LEADERBOARD========");
	for (size_t i = 0; i < users.size(); i++)
	{
		const User* user = users[i];
		std::println("{}: {} - Battles Won: {}, XP: {}, Win Rate: {:.2f}%",
			i + 1, user->getUsername().c_str(), user->getBattlesWon(), user->getXP(), user->getWinRate() * 100);
	}
	std::println("===========================\n");
}