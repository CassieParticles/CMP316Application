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

#include <imgui.h>

GameLoop::GameLoop():BaseGameLoop("Test window", 800, 800)
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
	cameraTrans->position = { 5,0,-2 };
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
	cube1Trans->position = DirectX::XMFLOAT3(2, 0, 8);
	cube1Trans->scale = DirectX::XMFLOAT3(1, 1, 1);
	spaceOneCube->addUpdateComponent<SpinTestComponent>();

	spaceOneCube2 = scene->CreateGameObject(0);
	MeshComponent* cube1Mesh2 = spaceOneCube2->addRenderComponent<MeshComponent>();
	cube1Mesh2->setMesh("Cube", meshLoader.get());
	cube1Mesh2->setTexture("Bunny", textureLoader.get());
	TransformComponent* cube1Trans2 = spaceOneCube2->getComponent<TransformComponent>();
	cube1Trans2->position = DirectX::XMFLOAT3(8, 0, 2);
	cube1Trans2->scale = DirectX::XMFLOAT3(1, 1, 1);
	spaceOneCube2->addUpdateComponent<SpinTestComponent>();

	//Create the portals
	portalA = scene->CreateGameObject(0);
	PortalComponent* portalAPortal = portalA->addRenderComponent<PortalComponent>();
	MeshComponent* portalAMesh = portalA->addRenderComponent<MeshComponent>();
	portalAPortal->setPlayer(playerObject);
	portalAPortal->SetScene(scene.get());
	portalAMesh->setMesh("Quad", meshLoader.get());
	portalA->getComponent<TransformComponent>()->position = DirectX::XMFLOAT3(5, 0, 5);
	portalA->getComponent<TransformComponent>()->scale = DirectX::XMFLOAT3(4, 4, 1);

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
	cube2Mesh->setTexture("Tom", textureLoader.get());
	TransformComponent* cube2Trans = spaceTwoCube->getComponent<TransformComponent>();
	cube2Trans->position = DirectX::XMFLOAT3(28, 0, 8);
	cube2Trans->scale = DirectX::XMFLOAT3(1, 1, 1);
	spaceTwoCube->addUpdateComponent<SpinTestComponent>();

	spaceTwoCube2 = scene->CreateGameObject(0);
	MeshComponent* cube2Mesh2 = spaceTwoCube2->addRenderComponent<MeshComponent>();
	cube2Mesh2->setMesh("Cube", meshLoader.get());
	cube2Mesh2->setTexture("Tom", textureLoader.get());
	TransformComponent* cube2Trans2 = spaceTwoCube2->getComponent<TransformComponent>();
	cube2Trans2->position = DirectX::XMFLOAT3(22, 0, 2);
	cube2Trans2->scale = DirectX::XMFLOAT3(1, 1, 1);
	spaceTwoCube2->addUpdateComponent<SpinTestComponent>();

	portalB = scene->CreateGameObject(0);
	PortalComponent* portalBPortal = portalB->addRenderComponent<PortalComponent>();
	MeshComponent* portalBMesh = portalB->addRenderComponent<MeshComponent>();
	portalBPortal->setPlayer(playerObject);
	portalBPortal->SetScene(scene.get());
	portalBMesh->setMesh("Quad", meshLoader.get());
	portalB->getComponent<TransformComponent>()->position = DirectX::XMFLOAT3(25, 0, 5);
	portalB->getComponent<TransformComponent>()->rotation = DirectX::XMFLOAT3(0, 3.14159f, 0);
	portalB->getComponent<TransformComponent>()->scale = DirectX::XMFLOAT3(4, 4, 1);

	
	portalAPortal->linkPortal(portalBPortal);
	portalBPortal->linkPortal(portalAPortal);


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

	if (rotatePortal)
	{
		portalB->getComponent<TransformComponent>()->rotation.y += timer->getDeltaTime();
	}
}

void GameLoop::physUpdate()
{
	BaseGameLoop::physUpdate();
}

void GameLoop::render()
{
	BaseGameLoop::render();
}

void GameLoop::guiRender()
{
	BaseGameLoop::guiRender();

	ImGui::Begin("Test window");

	ImGui::Text("Test window");
	ImGui::Checkbox("Render portals", &drawPortalInternals);
	ImGui::Checkbox("Rotate portal", &rotatePortal);

	ImGui::SliderAngle("Other portal angle", &portalB->getComponent<TransformComponent>()->rotation.y, 0, 360);

	ImGui::End();
}

void GameLoop::exit()
{
	BaseGameLoop::exit();

	std::cout <<"Average FPS: " << timer->getFPS() << '\n';
}
