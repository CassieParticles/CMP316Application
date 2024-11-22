#include <iostream>

#include "Game/GameLoop.h"

#include <vector>
#include <new>

int main()
{
	GameLoop gameLoop{};

	while (!gameLoop.getShouldClose())
	{
		gameLoop.loop();
	}

	gameLoop.exit();

	return 0;
}