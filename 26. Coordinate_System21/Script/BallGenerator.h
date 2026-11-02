#pragma once
#include "Component.h"
#include "../AllComponent.h"

class BallGenerator : public Component {
private:
	int count = 0;

public:
	void Start() override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};