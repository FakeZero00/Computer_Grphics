#pragma once
#include "Component.h"

class SquareMovement : public Component {
public:
	bool isMoving = false;
	bool combineReady = false;

	SquareMovement() = default;

	void OnTriggerStay(Object* other) override;

	void Update(float deltaTime) override;
};