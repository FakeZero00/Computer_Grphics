#pragma once
#include "Component.h"
#include "../AllComponent.h"

class Orbit : public Component {
private:
	Transform* tr;

public:
	void Start() override;
	void Update(float deltaTime) override;
};