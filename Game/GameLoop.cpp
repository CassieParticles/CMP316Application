#include "GameLoop.h"

#include <engine/ObjectStructure/GameObject.h>

#include <engine/Rendering/MeshComponent.h>
#include <graphicsEngine/VectorMathOverloads.h>
#include <glfw3.h>

#include <graphicsEngine/Pipeline/Shader.h>


GameLoop::GameLoop():BaseGameLoop("Test window", 800, 600)
{
	//Create test game object
	gameObject = new GameObject{ device,deviceContext };
	MeshComponent* mesh = gameObject->addRenderComponent<MeshComponent>();
	mesh->setMesh("Plane", meshLoader.get());

	TransformComponent* transComp = gameObject->getComponent<TransformComponent>();
	transComp->scale.x = 20;
	transComp->scale.y = 20;
	transComp->scale.z = 2;
	transComp->position.x = 3;

	view = new View{ device.Get(),{0,10,0},{85 * 3.14159f / 180,0,0} };
}

GameLoop::~GameLoop()
{
	delete gameObject;
	delete view;
}

void GameLoop::handleInput()
{
	if (input->getKeyDown(GLFW_KEY_D))
	{
		view->setRotation(view->loadRotation() + DirectX::XMVECTOR{ 0, 0.001f, 0, 0 });
	}
	if (input->getKeyDown(GLFW_KEY_A))
	{
		view->setRotation(view->loadRotation() + DirectX::XMVECTOR{ 0, -0.001f, 0, 0 });
	}
}

void GameLoop::update()
{
}

void GameLoop::render()
{
	window->clearBackBuffer();
	window->bindRenderTarget();

	view->updateView(deviceContext.Get());

	inputLayout.useInputLayout(deviceContext.Get());
	//mesh->useMesh(deviceContext.Get());

	baseVertexShader->bindShader(deviceContext.Get());
	baseVertexShader->bindShader(deviceContext.Get());



	ID3D11Buffer* cBuffers[1]{ view->getCameraBuffer() };

	deviceContext->VSSetConstantBuffers(0, 1, cBuffers);



	//mesh2->useMesh(deviceContext.Get());
	gameObject->getComponent<MeshComponent>()->Render();

	window->presentBackBuffer();
}
