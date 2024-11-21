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
protected:
	double time{};
	bool leftRight = false;

	GameObject* gameObject;
	GameObject* cameraObject;
};