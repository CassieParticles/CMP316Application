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
	GameObject* gameObject;
	GameObject* gameObject2;
	GameObject* gameObject3;

	int currentScene{};

	GameObject* cameraObject;
};