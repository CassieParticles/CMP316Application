#include "GameLoop.h"

#include <glfw3.h>

#include <engine/ObjectStructure/GameObject.h>
#include <engine/Rendering/Components/MeshComponent.h>

#include <graphicsEngine/VectorMathOverloads.h>
#include <graphicsEngine/Pipeline/Shader.h>
#include <engine/Rendering/Components/CameraComponent.h>


GameLoop::GameLoop():BaseGameLoop("Test window", 800, 600)
{
	timer->setMaxFrameRate(150);
	//Create test game object cube
	gameObject = scene->createGameObject(0);
	MeshComponent* mesh = gameObject->addRenderComponent<MeshComponent>();
	TransformComponent* cubeTrans = gameObject->getComponent<TransformComponent>();
	cubeTrans->position.z = 2;
	mesh->setMesh("Cube", meshLoader.get());

	TransformComponent* transComp = gameObject->getComponent<TransformComponent>();

	//Create camera object
	cameraObject = scene->createGameObject(0);
	TransformComponent* cameraTrans = cameraObject->getComponent<TransformComponent>();
	cameraTrans->position = { 0,0,0 };
	CameraComponent* camera = cameraObject->addRenderComponent<CameraComponent>();
	camera->setProjectionMatrixPespective(89.9 * 3.14159f / 180, window->getAspectRatio(), 0.1f, 1000.f);
	input->setMouseCentred(false);
}

GameLoop::~GameLoop()
{

}

void GameLoop::handleInput()
{
	BaseGameLoop::handleInput();

	if (input->getKeyPressed(GLFW_KEY_L))
	{
		input->setMouseCentred(!input->getMouseCentred());
		std::cout << "Centred\n";
	}
}

void GameLoop::update()
{
	BaseGameLoop::handleInput();
	gameObject->getComponent<TransformComponent>()->rotation.x += 2 * 3.14159f * timer->getDeltaTime() * (leftRight ? 1 : -1);
}

void GameLoop::render()
{
	BaseGameLoop::render();
	window->clearBackBuffer();
	window->bindRenderTarget();

	//gameObject->getComponent<MeshComponent>()->Render();

	//cameraObject->getComponent<CameraComponent>()->Render();

}
