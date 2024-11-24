#include "GameLoop.h"

#include <GLFW/glfw3.h>

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

	timer->setMaxFrameRate(150);

	//Create test game object cube
	gameObject = scene->CreateGameObject(0);
	MeshComponent* mesh = gameObject->addRenderComponent<MeshComponent>();
	TransformComponent* cubeTrans = gameObject->getComponent<TransformComponent>();
	cubeTrans->position.z = 2;
	mesh->setMesh("Cube", meshLoader.get());
	mesh->setTexture("Bunny", textureLoader.get());

	//Create test game object cube
	gameObject2 = scene->CreateGameObject(0);
	MeshComponent* mesh2 = gameObject2->addRenderComponent<MeshComponent>();
	TransformComponent* cubeTrans2 = gameObject2->getComponent<TransformComponent>();
	cubeTrans2->position.z = 2;
	cubeTrans2->position.x = 2;
	mesh2->setMesh("Cube", meshLoader.get());
	mesh2->setTexture("Bunny", textureLoader.get());

	//Create test game object cube
	gameObject3 = scene->CreateGameObject(0);
	MeshComponent* mesh3 = gameObject3->addRenderComponent<MeshComponent>();
	TransformComponent* cubeTrans3 = gameObject3->getComponent<TransformComponent>();
	cubeTrans3->position.z = 2;
	cubeTrans3->position.x = -2;
	mesh3->setMesh("Cube", meshLoader.get());
	mesh3->setTexture("Bunny", textureLoader.get());
	

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

	setPlayer(&cameraObject);
}

GameLoop::~GameLoop()
{

}

void GameLoop::handleInput()
{
	BaseGameLoop::handleInput();

	if (input->getKeyPressed(GLFW_KEY_G))
	{
		std::cout << "Moved object\n";
		gameObject = scene->moveGameObject(currentObjectScene, 1 - currentObjectScene, gameObject);
		currentObjectScene = 1 - currentObjectScene;
	}

	if (input->getKeyPressed(GLFW_KEY_M))
	{
		std::cout << "Moved player\n";
		cameraObject = scene->moveGameObject(currentScene, 1 - currentScene, cameraObject);
		currentScene = 1 - currentScene;
	}
}

void GameLoop::update()
{
	BaseGameLoop::update();
	gameObject->getComponent<TransformComponent>()->rotation.x += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;
	gameObject->getComponent<TransformComponent>()->rotation.y += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;
	gameObject->getComponent<TransformComponent>()->rotation.z += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;

	gameObject2->getComponent<TransformComponent>()->rotation.x += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;
	gameObject2->getComponent<TransformComponent>()->rotation.y += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;
	gameObject2->getComponent<TransformComponent>()->rotation.z += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;

	gameObject3->getComponent<TransformComponent>()->rotation.x += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;
	gameObject3->getComponent<TransformComponent>()->rotation.y += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;
	gameObject3->getComponent<TransformComponent>()->rotation.z += 2 * 3.14159f * static_cast<float>(timer->getDeltaTime()) * 0.25f;
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
