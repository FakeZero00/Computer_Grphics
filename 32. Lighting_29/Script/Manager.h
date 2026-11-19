#pragma once
#include "Component.h"
#include "../AllComponent.h"
#include "Object.h"

class Manager : public Component {
private:
	Object* lightArm;
	Transform* lightArmTf;

	Object* lightObj;
	Transform* lightTf;
	Light* light;

	InputManager* inputManager;

public:
	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};