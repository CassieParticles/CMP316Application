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
	gameObject = new GameObject{ device,deviceContext,renderer.get()};
	MeshComponent* mesh = gameObject->addRenderComponent<MeshComponent>();
	TransformComponent* cubeTrans = gameObject->getComponent<TransformComponent>();
	cubeTrans->position.z = 2;
	mesh->setMesh("Cube", meshLoader.get());

	TransformComponent* transComp = gameObject->getComponent<TransformComponent>();

	//Create camera object
	cameraObject = new GameObject{ device,deviceContext,renderer.get()};
	TransformComponent* cameraTrans = cameraObject->getComponent<TransformComponent>();
	cameraTrans->position = { 0,0,0 };
	CameraComponent* camera = cameraObject->addRenderComponent<CameraComponent>();
	camera->setProjectionMatrixPespective(89.9 * 3.14159f / 180, window->getAspectRatio(), 0.1f, 1000.f);
}

GameLoop::~GameLoop()
{
	delete gameObject;
	delete cameraObject;
}

void GameLoop::handleInput()
{
	BaseGameLoop::handleInput();
	TransformComponent* cameraTrans = cameraObject->getComponent<TransformComponent>();
	if (input->getKeyDown(GLFW_KEY_D))
	{
		cameraTrans->rotation.y += 0.001f;
	}
	if (input->getKeyDown(GLFW_KEY_A))
	{
		cameraTrans->rotation.y -= 0.001f;
	}
	if (input->getKeyDown(GLFW_KEY_W))
	{
		cameraTrans->rotation.x -= 0.001f;
	}
	if (input->getKeyDown(GLFW_KEY_S))
	{
		cameraTrans->rotation.x += 0.001f;
	}
}

void GameLoop::update()
{
	//cameraObject->getComponent<TransformComponent>()->position.y+= 0.0001f;
	gameObject->getComponent<TransformComponent>()->rotation.x += 0.001f;
	gameObject->getComponent<TransformComponent>()->rotation.y += 0.001f;
	gameObject->getComponent<TransformComponent>()->rotation.z += 0.001f;

	gameObject->getComponent<TransformComponent>()->position.z += 0.001f;
	cameraObject->getComponent<TransformComponent>()->position.z += 0.001f;
}

void GameLoop::render()
{
	window->clearBackBuffer();
	window->bindRenderTarget();

	gameObject->getComponent<MeshComponent>()->Render();

	cameraObject->getComponent<CameraComponent>()->Render();

	renderer->draw();

	window->presentBackBuffer();
}
