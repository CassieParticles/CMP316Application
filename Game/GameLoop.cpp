#include "GameLoop.h"

#include <glfw3.h>

#include <engine/ObjectStructure/GameObject.h>
#include <engine/Rendering/Components/MeshComponent.h>
#include <engine/Rendering/Components/PlayerCameraComponent.h>

#include <graphicsEngine/VectorMathOverloads.h>

#include "Player/ControllerComponent.h"
#include "Player/PlayerMoveComponent.h"


GameLoop::GameLoop():BaseGameLoop("Test window", 1200, 1200)
{
	//Load assets
	textureLoader->loadTextureFromFile("Bunny", "Assets/bunny.png");
	textureLoader->addColour("Red", 1, 0, 0);

	timer->setMaxFrameRate(-1);

	//Create test game object cube
	gameObject = scene->CreateGameObject(0);
	MeshComponent* mesh = gameObject->addRenderComponent<MeshComponent>();
	TransformComponent* cubeTrans = gameObject->getComponent<TransformComponent>();
	cubeTrans->position.z = 2;
	mesh->setMesh("Cube", meshLoader.get());
	mesh->setTexture("Bunny", textureLoader.get());

	TransformComponent* transComp = gameObject->getComponent<TransformComponent>();

	//Create camera object
	cameraObject = scene->CreateGameObject(0);
	TransformComponent* cameraTrans = cameraObject->getComponent<TransformComponent>();
	cameraTrans->position = { 0,0,0 };
	PlayerCameraComponent* camera = cameraObject->addRenderComponent<PlayerCameraComponent>();
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
	gameObject->getComponent<TransformComponent>()->rotation.x += 2 * 3.14159f * timer->getDeltaTime() * 0.25f;
	gameObject->getComponent<TransformComponent>()->rotation.y += 2 * 3.14159f * timer->getDeltaTime() * 0.25f;
	gameObject->getComponent<TransformComponent>()->rotation.z += 2 * 3.14159f * timer->getDeltaTime() * 0.25f;
}

void GameLoop::render()
{
	BaseGameLoop::render();
	window->clearBackBuffer();
	window->bindRenderTarget();
}

void GameLoop::exit()
{
	BaseGameLoop::exit();

	std::cout <<"Average FPS: " << timer->getFPS() << '\n';
}
