#pragma once
#include "Component.h"
#include "../AllComponent.h"

class Planet : public Component {
private:
	Transform* tr;
	MeshRenderer3D* mr;

public:
	bool isCenter = false;

	void Start() override;
	void Update(float deltaTime) override;
};