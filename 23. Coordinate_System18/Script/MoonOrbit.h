#pragma once
#include "Component.h"
#include "../AllComponent.h"

class MoonOrbit : public Component {
private:
	Transform* tr;
	Transform* parentTr;

	bool isScaling = false;
	float scaleWeight = 0.0f;

	bool isRotating = false;

public:
	Object* parentPlanet;

	MoonOrbit(Object* parentPlanet) : parentPlanet(parentPlanet) {};

	void Start() override;
	void Update(float deltaTime) override;
};