#include "GameEngine.h"
#include <cstdlib>
#include <ctime>

GameEngine gameEngine;

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	gameEngine.run();
}