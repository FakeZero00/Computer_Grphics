#pragma once
#include "Component.h"
#include "../AllComponent.h"

class PlanetManager : public Component {
public:
	Camera* cam;

	PlanetManager(Camera* cam) : cam(cam) {};

	void Update(float deltaTime) override;
};