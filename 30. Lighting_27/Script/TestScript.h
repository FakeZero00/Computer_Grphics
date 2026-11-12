#pragma once
#include "Component.h"
#include "../AllComponent.h"
#include "Object.h"

class TestScript : public Component {
private:
	Transform* tr;
	InputManager* inputManager;

	Object* lightObj;
	Light* light;

	vec4 lightColor[3] = {
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(0.0f, 1.0f, 0.0f, 1.0f),
		vec4(0.0f, 0.0f, 1.0f, 1.0f)
	};
	int currentColorIndex = 0;
	float rotateSpeed = 90.0f;

public:
	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};