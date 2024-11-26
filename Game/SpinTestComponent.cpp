#include "SpinTestComponent.h"

#include <engine/ObjectStructure/DefaultComponents/TransformComponent.h>
#include <engine/ObjectStructure/GameObject.h>

SpinTestComponent::SpinTestComponent(GameObject* gameObject):UpdateComponent{gameObject}
{

}

void SpinTestComponent::Update(Timer* timer)
{
	TransformComponent* trans = gameObject->getComponent<TransformComponent>();
	trans->rotation.x += static_cast<float>(timer->getDeltaTime()) * 2 * 3.14159f;
	trans->rotation.y += static_cast<float>(timer->getDeltaTime()) * 2 * 3.14159f;
	trans->rotation.z += static_cast<float>(timer->getDeltaTime()) * 2 * 3.14159f;
}

