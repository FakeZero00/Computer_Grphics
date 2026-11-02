#pragma once
#include "Component.h"
#include "../AllComponent.h"

class SBGenerator : public Component {
public:
	void Start() override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};