#pragma once
#include "Position2D.h"
#include "Component.h"

class SquareMovement : public Component {
public:
	SquareMovement() = default;

	void Update(float deltaTime) override;
private:
	//제어변수
	int MoveMode = 0;
	bool clockmove = false;

	//속도
	Position2D velocity{ 0.0f, 0.0f };
};