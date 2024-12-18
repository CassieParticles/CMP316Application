#include "GameLoop.h"

#include <GLFW/glfw3.h>

#include <engine/ObjectStructure/GameObject.h>
#include <engine/Rendering/Components/MeshComponent.h>
#include <engine/Rendering/Components/PlayerCameraComponent.h>
#include <engine/Rendering/Components/Portal/PortalComponent.h>

#include <graphicsEngine/VectorMathOverloads.h>

#include "Player/ControllerComponent.h"
#include "Player/PlayerMoveComponent.h"
#include "SpinTestComponent.h"
#include <engine/Rendering/Components/Portal/PortalEndComponent.h>


GameLoop::GameLoop():BaseGameLoop("Test window", 1200, 1200)
{
	window->changeClearColour(DirectX::XMFLOAT4(0.2, 0.4, 0.6, 1.0));
	//Load assets
	textureLoader->loadTextureFromFile("Bunny", "Assets/bunny.png");
	textureLoader->loadTextureFromFile("Tom", "Assets/Scom tott.png");
	textureLoader->addColour("Red", 1, 0, 0);

	timer->setMaxFrameRate(150);

	//Create player
	playerObject = scene->CreateGameObject(0);
	TransformComponent* cameraTrans = playerObject->getComponent<TransformComponent>();
	cameraTrans->position = { 0,0,0 };
	PlayerCameraComponent* camera = playerObject->addRenderComponent<PlayerCameraComponent>();
	camera->setProjectionMatrixPespective(89.9 * 3.14159f / 180, window->getAspectRatio(), 0.1f, 1000.f);
	input->setMouseCentred(false);
	playerObject->addInputComponent<ControllerComponent>()->setMoveSpeed(5);
	playerObject->addUpdateComponent<PlayerMoveComponent>();

	setPlayer(&playerObject);

	//Create the scene

	//First space
	spaceOneFloor = scene->CreateGameObject(0);
	MeshComponent* floor1Mesh = spaceOneFloor->addRenderComponent<MeshComponent>();
	floor1Mesh->setMesh("Plane", meshLoader.get());
	floor1Mesh->setTexture("Bunny", textureLoader.get());
	TransformComponent* floor1Trans = spaceOneFloor->getComponent<TransformComponent>();
	floor1Trans->position = DirectX::XMFLOAT3(0, -2, 0);
	floor1Trans->scale = DirectX::XMFLOAT3(10, 1, 10);

	spaceOneCube = scene->CreateGameObject(0);
	MeshComponent* cube1Mesh = spaceOneCube->addRenderComponent<MeshComponent>();
	cube1Mesh->setMesh("Cube", meshLoader.get());
	cube1Mesh->setTexture("Bunny", textureLoader.get());
	TransformComponent* cube1Trans = spaceOneCube->getComponent<TransformComponent>();
	cube1Trans->position = DirectX::XMFLOAT3(5, 0, 5);
	cube1Trans->scale = DirectX::XMFLOAT3(1, 1, 1);
	spaceOneCube->addUpdateComponent<SpinTestComponent>();

	//Second space
	spaceTwoFloor = scene->CreateGameObject(0);
	MeshComponent* floor2Mesh = spaceTwoFloor->addRenderComponent<MeshComponent>();
	floor2Mesh->setMesh("Plane", meshLoader.get());
	floor2Mesh->setTexture("Tom", textureLoader.get());
	TransformComponent* floor2Trans = spaceTwoFloor->getComponent<TransformComponent>();
	floor2Trans->position = DirectX::XMFLOAT3(20, -2, 0);
	floor2Trans->scale = DirectX::XMFLOAT3(10, 1, 10);

	spaceTwoCube = scene->CreateGameObject(0);
	MeshComponent* cube2Mesh = spaceTwoCube->addRenderComponent<MeshComponent>();
	cube2Mesh->setMesh("Cube", meshLoader.get());
	//cube2Mesh->setTexture("Tom", textureLoader.get());
	TransformComponent* cube2Trans = spaceTwoCube->getComponent<TransformComponent>();
	cube2Trans->position = DirectX::XMFLOAT3(25, 0, 5);
	cube2Trans->scale = DirectX::XMFLOAT3(1, 1, 1);
	spaceTwoCube->addUpdateComponent<SpinTestComponent>();

	//Create the portals
	portalA = scene->CreateGameObject(0);
	portalA->addRenderComponent<PortalComponent>();
	MeshComponent* portalAMesh = portalA->addRenderComponent<MeshComponent>();
	portalA->addRenderComponent<PortalEndComponent>();
	portalAMesh->setMesh("Quad", meshLoader.get());
	portalA->getComponent<TransformComponent>()->position = DirectX::XMFLOAT3(5, 0, 0);
	portalA->getComponent<TransformComponent>()->scale = DirectX::XMFLOAT3(2, 4, 1);
	
	portalB = scene->CreateGameObject(0);
	portalB->addRenderComponent<PortalComponent>();
	MeshComponent* portalBMesh = portalB->addRenderComponent<MeshComponent>();
	portalB->addRenderComponent<PortalEndComponent>();
	portalBMesh->setMesh("Quad", meshLoader.get());
	portalB->getComponent<TransformComponent>()->position = DirectX::XMFLOAT3(25, 0, 0);
	portalB->getComponent<TransformComponent>()->scale = DirectX::XMFLOAT3(2, 4, 1);

}

GameLoop::~GameLoop()
{

}

void GameLoop::handleInput()
{
	BaseGameLoop::handleInput();

	if (input->getKeyPressed(GLFW_KEY_M))
	{
		std::cout << "Moved player\n";
		playerObject = scene->moveGameObject(currentScene, 1 - currentScene, playerObject);
		currentScene = 1 - currentScene;
	}
}

void GameLoop::update()
{
	BaseGameLoop::update();
}

void GameLoop::render()
{
	BaseGameLoop::render();
}

void GameLoop::exit()
{
	BaseGameLoop::exit();

	std::cout <<"Average FPS: " << timer->getFPS() << '\n';
}
