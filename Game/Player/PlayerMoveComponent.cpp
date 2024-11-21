#include "PlayerMoveComponent.h"

#include <engine/ObjectStructure/GameObject.h>
#include <graphicsEngine/VectorMathOverloads.h>

PlayerMoveComponent::PlayerMoveComponent(GameObject* gameObject) :UpdateComponent{ gameObject }
{
	moveDirection = DirectX::XMFLOAT3(0, 0, 0);
}

PlayerMoveComponent::PlayerMoveComponent(PlayerMoveComponent& other) :UpdateComponent{ other }
{
	other.moveDirection = moveDirection;
}

PlayerMoveComponent::PlayerMoveComponent(PlayerMoveComponent&& other):UpdateComponent{other}
{
	other.moveDirection = std::move(moveDirection);
}

PlayerMoveComponent::~PlayerMoveComponent()
{

}

void PlayerMoveComponent::Update(Timer* timer)
{
	TransformComponent* transform = gameObject->getComponent<TransformComponent>();

	DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&transform->position);
	DirectX::XMVECTOR travelDist = DirectX::XMLoadFloat3(&moveDirection);
	
	pos += travelDist * timer->getDeltaTime();

	DirectX::XMStoreFloat3(&transform->position, pos);

	moveDirection = DirectX::XMFLOAT3(0,0,0);
}
