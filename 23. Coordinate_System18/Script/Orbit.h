#pragma once
#include "Component.h"
#include "../AllComponent.h"

class Orbit : public Component {
private:
	Transform* tr;

	bool isScaling = false;
	float scaleWeight = 0.0f;

public:
	void Start() override;
	void Update(float deltaTime) override;
};