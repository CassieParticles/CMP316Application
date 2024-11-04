#include "GameLoop.h"

#include <glfw3.h>

#include <engine/ObjectStructure/GameObject.h>
#include <engine/Rendering/MeshComponent.h>

#include <graphicsEngine/VectorMathOverloads.h>
#include <graphicsEngine/Pipeline/Shader.h>


GameLoop::GameLoop():BaseGameLoop("Test window", 800, 600)
{
	//Create test game object
	gameObject = new GameObject{ device,deviceContext };
	MeshComponent* mesh = gameObject->addRenderComponent<MeshComponent>();
	mesh->setMesh("Cube", meshLoader.get());

	TransformComponent* transComp = gameObject->getComponent<TransformComponent>();
	//transComp->scale.x = 200;
	//transComp->scale.y = 200;
	//transComp->scale.z = 200;
	//transComp->position.x = -100;
	//transComp->position.z = -100;



	view = new View{ device.Get(),{0,0,-10},{0,0,0} };
	view->setProjectionMatrixPespective(89 * 3.14159f / 180, window->getAspectRatio(), 0.1f, 1000.f);
}

GameLoop::~GameLoop()
{
	delete gameObject;
	delete view;
}

void GameLoop::handleInput()
{
	BaseGameLoop::handleInput();
	if (input->getKeyDown(GLFW_KEY_D))
	{
		view->setRotation(view->loadRotation() + DirectX::XMVECTOR{ 0, 0.00001f, 0, 0 });
	}
	if (input->getKeyDown(GLFW_KEY_A))
	{
		view->setRotation(view->loadRotation() + DirectX::XMVECTOR{ 0, -0.00001f, 0, 0 });
	}
	if (input->getKeyDown(GLFW_KEY_W))
	{
		view->setRotation(view->loadRotation() + DirectX::XMVECTOR{ -0.00001f, 0, 0, 0 });
	}
	if (input->getKeyDown(GLFW_KEY_S))
	{
		view->setRotation(view->loadRotation() + DirectX::XMVECTOR{ 0.00001f, 0, 0, 0 });
	}
}

void GameLoop::update()
{
	gameObject->getComponent<TransformComponent>()->position.z+= 0.001f;
}

void GameLoop::render()
{
	window->clearBackBuffer();
	window->bindRenderTarget();

	view->updateView(deviceContext.Get());

	inputLayout.useInputLayout(deviceContext.Get());

	baseVertexShader->bindShader(deviceContext.Get());
	basePixelShader->bindShader(deviceContext.Get());

	ID3D11Buffer* cBuffers[1]{ view->getCameraBuffer() };

	deviceContext->VSSetConstantBuffers(0, 1, cBuffers);

	gameObject->getComponent<MeshComponent>()->Render();

	window->presentBackBuffer();
}
