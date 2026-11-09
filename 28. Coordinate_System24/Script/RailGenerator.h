#pragma once
#include "../AllComponent.h"
#include "Component.h"

class RailGenerator : public Component {

public:
	int count;
	vec3 startPos1 = vec3(-0.99f, 0.94f, 2.96f);
	vec3 endPos1 = vec3(-0.99f, 0.94f, -2.02f);
	vec3 startPos2 = vec3(-0.99f, 0.94f, -2.02f);
	vec3 endPos2 = vec3(3.14f, 0.94f, -2.02f);

	void Start() override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};