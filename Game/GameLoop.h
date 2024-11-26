#pragma once

#include <engine/BaseGameLoop.h>
#include <engine/ObjectStructure/GameObject.h>


class GameLoop : public BaseGameLoop
{
public:
	GameLoop();
	~GameLoop();

	void handleInput() override;
	void update() override;
	void render() override;

	void exit() override;
protected:


	int currentScene{};
	int currentObjectScene{};

	GameObject* playerObject;

	GameObject* spaceOneFloor;
	GameObject* spaceOneCube;

	GameObject* spaceTwoFloor;
	GameObject* spaceTwoCube;

	GameObject* portalA;
	GameObject* portalB;
};