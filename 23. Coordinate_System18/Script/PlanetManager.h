#pragma once
#include "Component.h"
#include "../AllComponent.h"

class PlanetManager : public Component {
public:
	Camera* cam;
	Transform* centerTr;

	PlanetManager(Camera* cam, Transform* centerTr) : cam(cam), centerTr(centerTr) {};

	void Update(float deltaTime) override;
};