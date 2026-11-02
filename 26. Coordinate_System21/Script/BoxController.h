#pragma once
#include "Component.h"
#include "../AllComponent.h"

class BoxController : public Component {
private:
	Transform* tr;
	float rotationSpeed = 100.0f;

	float currentMousePos;
	float lastMousePos;

public:
	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};