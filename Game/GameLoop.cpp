#include "GameLoop.h"

#include <glfw3.h>

#include <engine/ObjectStructure/GameObject.h>
#include <engine/Rendering/Components/MeshComponent.h>

#include <graphicsEngine/VectorMathOverloads.h>
#include <graphicsEngine/Pipeline/Shader.h>
#include <engine/Rendering/Components/CameraComponent.h>


GameLoop::GameLoop():BaseGameLoop("Test window", 800, 600)
{
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

}

GameLoop::~GameLoop()
{

}

void GameLoop::handleInput()
{
	BaseGameLoop::handleInput();
	TransformComponent* cameraTrans = cameraObject->getComponent<TransformComponent>();
	if (input->getKeyDown(GLFW_KEY_D))
	{
		//cameraTrans->rotation.y += 0.001f;
		std::cout << timer->getDeltaTime()<<'\n';
	}
	if (input->getKeyDown(GLFW_KEY_A))
	{
		std::cout << timer->getDeltaTime() << '\n';
	}
	if (input->getKeyDown(GLFW_KEY_W))
	{
		std::cout << timer->getDeltaTime() << '\n';
	}
	if (input->getKeyDown(GLFW_KEY_S))
	{
		std::cout << timer->getDeltaTime() << '\n';
	}
}

void GameLoop::update()
{
	BaseGameLoop::handleInput();
	gameObject->getComponent<TransformComponent>()->rotation.x += 2 * 3.14159f * timer->getDeltaTime() * (leftRight ? 1 : -1);
	//gameObject->getComponent<TransformComponent>()->rotation.y += 2 * 3.14159f * timer->getDeltaTime();
	//gameObject->getComponent<TransformComponent>()->rotation.z += 2 * 3.14159f * timer->getDeltaTime();

	gameObject->getComponent<TransformComponent>()->position.z += 1 * timer->getDeltaTime();
	cameraObject->getComponent<TransformComponent>()->position.z += 1 * timer->getDeltaTime();

	time += timer->getDeltaTime();
	if (time > 1)
	{
		std::cout << "=======================1 second has passed==================\n";
		time-=1;
		leftRight = !leftRight;
	}
}

void GameLoop::render()
{
	BaseGameLoop::render();
	window->clearBackBuffer();
	window->bindRenderTarget();

	//gameObject->getComponent<MeshComponent>()->Render();

	//cameraObject->getComponent<CameraComponent>()->Render();

}
