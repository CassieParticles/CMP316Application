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
	void guiRender() override;

	void exit() override;
protected:


	int currentScene{};
	int currentObjectScene{};

	bool rotatePortal{ false };

	GameObject* playerObject;

	GameObject* spaceOneFloor;
	GameObject* spaceOneCube;
	GameObject* spaceOneCube2;

	GameObject* spaceTwoFloor;
	GameObject* spaceTwoCube;
	GameObject* spaceTwoCube2;

	GameObject* portalA;
	GameObject* portalB;
};