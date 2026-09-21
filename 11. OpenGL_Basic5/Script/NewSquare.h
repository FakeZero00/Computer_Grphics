#pragma once
#include "Component.h"
#include "Object.h"

class NewSquare : public Component {
public:
	float timer = 3.0f;

	void Update(float deltaTime) override;
};