#include "ControllerComponent.h"

#include <engine/ObjectStructure/GameObject.h>

#include <glfw3.h>

#include "PlayerMoveComponent.h"

ControllerComponent::ControllerComponent(GameObject* gameObject):InputComponent{gameObject}
{

}

ControllerComponent::ControllerComponent(ControllerComponent& other):InputComponent{other}
{

}

ControllerComponent::ControllerComponent(ControllerComponent&& other):InputComponent{other}
{

}

ControllerComponent::~ControllerComponent()
{
}

void ControllerComponent::Input(InputHandler* input)
{
	PlayerMoveComponent* playerMoveComp = gameObject->getComponent<PlayerMoveComponent>();

	if (input->getKeyDown(GLFW_KEY_W))
	{
		playerMoveComp->moveDirection.z += 1;
	}
	if (input->getKeyDown(GLFW_KEY_S))
	{
		playerMoveComp->moveDirection.z -= 1;
	}
	if (input->getKeyDown(GLFW_KEY_A))
	{
		playerMoveComp->moveDirection.x -= 1;
	}
	if (input->getKeyDown(GLFW_KEY_D))
	{
		playerMoveComp->moveDirection.x += 1;
	}
}
