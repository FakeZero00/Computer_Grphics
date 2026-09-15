#pragma once
#include "Component.h"

class SquareGenerator : public Component {
public:
	float width = 0.2f;
	float height = 0.2f;

	SquareGenerator() = default;

	void CreateSquare();

	void Update(float deltaTime) override;
};