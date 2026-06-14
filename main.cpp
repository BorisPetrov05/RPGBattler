#include "GameEngine.h"
#include <cstdlib>
#include <ctime>

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	GameEngine gameEngine;
	gameEngine.run();
}