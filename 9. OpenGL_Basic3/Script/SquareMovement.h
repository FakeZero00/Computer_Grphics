#pragma once
#include "Component.h"

class SquareMovement : public Component {
public:
	bool isMoving = false;

	SquareMovement() = default;

	void Update(float deltaTime) override;
};