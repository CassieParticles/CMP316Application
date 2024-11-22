#include "GameLoop.h"

#include <glfw3.h>

#include <engine/ObjectStructure/GameObject.h>
#include <engine/Rendering/Components/MeshComponent.h>
#include <engine/Rendering/Components/CameraComponent.h>

#include <graphicsEngine/VectorMathOverloads.h>

#include "Player/ControllerComponent.h"
#include "Player/PlayerMoveComponent.h"

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
	cameraObject->addInputComponent<ControllerComponent>()->setMoveSpeed(5);
	cameraObject->addUpdateComponent<PlayerMoveComponent>();

}

GameLoop::~GameLoop()
{

}

void GameLoop::handleInput()
{
	BaseGameLoop::handleInput();
}

void GameLoop::update()
{
	BaseGameLoop::update();
	gameObject->getComponent<TransformComponent>()->rotation.x += 2 * 3.14159f * timer->getDeltaTime();
	gameObject->getComponent<TransformComponent>()->rotation.y += 2 * 3.14159f * timer->getDeltaTime();
	gameObject->getComponent<TransformComponent>()->rotation.z += 2 * 3.14159f * timer->getDeltaTime();
}

void GameLoop::render()
{
	BaseGameLoop::render();
	window->clearBackBuffer();
	window->bindRenderTarget();

	//gameObject->getComponent<MeshComponent>()->Render();

	//cameraObject->getComponent<CameraComponent>()->Render();

}
