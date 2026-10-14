#pragma once
#include "Component.h"
#include "../AllComponent.h"

class MoonOrbit : public Component {
private:
	Transform* tr;
	Transform* parentTr;

public:
	Object* parentPlanet;

	MoonOrbit(Object* parentPlanet) : parentPlanet(parentPlanet) {};

	void Start() override;
	void Update(float deltaTime) override;
};