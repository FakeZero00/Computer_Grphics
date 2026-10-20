#pragma once
#include "Component.h"
#include "../AllComponent.h"

class TestScript : public Component {
private:
	Transform* tr;

public:
	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};