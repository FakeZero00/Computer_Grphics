#pragma once
#include "Component.h"
#include "Object.h"
#include "../AllComponent.h"

class TestScript : public Component {
private:
	Object* lightObj;
	Transform* lightObjTr;
	Light* light;

	Object* objRoot;
	Transform* objRootTr;

	Object* orbitObj;
	Transform* orbitTr;
	Object* orbitChild;
	Transform* orbitChildTr;

	InputManager* inputManager;

	bool isLightOn = true;

public:
	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};