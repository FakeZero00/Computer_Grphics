#pragma once
#include "Component.h"
#include "Position2D.h"

class Particle : public Component {
private:
	Position2D velocity;
	bool toLight = false;

public:
	Particle(float vx, float vy, bool toLight) : velocity{ vx, vy }, toLight(toLight) {}

	void Update(float deltaTime) override;
};