#include <iostream>

#include "Game/GameLoop.h"

#include <vector>
#include <new>

int main()
{

	GameLoop gameLoop{};

	while (!gameLoop.getShouldClose())
	{
		gameLoop.handleInput();
		gameLoop.update();
		gameLoop.render();
	}

	return 0;
}