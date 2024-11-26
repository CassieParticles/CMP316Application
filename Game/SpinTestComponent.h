#pragma once

#include <engine/ObjectStructure/UpdateComponent.h>

class SpinTestComponent : public UpdateComponent
{
public:
	SpinTestComponent(GameObject* gameObject);
	
	void Update(Timer* timer) override;
protected:
};