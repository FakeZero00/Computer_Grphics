#pragma once
#include "Component.h"

class ObjectRotate : public Component {
public:
	float speed = 500.0f;

	void Update(float deltaTime) override;
};
