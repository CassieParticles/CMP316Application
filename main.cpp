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

	return 0;
}