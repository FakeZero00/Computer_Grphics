#pragma once
#include "Component.h"
#include "../AllComponent.h"

class Planet : public Component {
private:
	Transform* tr;
	MeshRenderer3D* mr;
	Transform* centerAnchorTr;

public:
	bool isCenter = false;

	bool isScaling = false;
	float scaleWeight = 0.0f;
	float colorWeight = 0.0f;
	bool isScaleUp = true;
	int colorMode = 0; // 0: Red, 1: Green, 2: Blue

	Object* centerAnchor;

	void Start() override;
	void Update(float deltaTime) override;
};