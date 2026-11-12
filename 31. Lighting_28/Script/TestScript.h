#pragma once
#include "Component.h"
#include "../AllComponent.h"
#include "Object.h"

class TestScript : public Component {
private:
	Transform* tr;
	
	Object* lightObj;
	Light* light;

	Object* lightRoot;
	Transform* lightRootTr;

	InputManager* inputManager;

	bool isLight = true;

	vec4 lightColor[3] = {
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		vec4(0.0f, 1.0f, 0.0f, 1.0f),
		vec4(0.0f, 0.0f, 1.0f, 1.0f)
	};
	int currentColorIndex = 0;

	float rotateSpeed = 90.0f;
	bool isYRotating = false;
	bool isRYRotating = false;
	bool isRRotating = false;
	bool isRRRotating = false;

public:
	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};