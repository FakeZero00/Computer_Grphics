#pragma once
#include "Component.h"
#include "../AllComponent.h"
#include "Object.h"

class Door : public Component {
private:
	Transform* tr;

	vec3 startPos = vec3(0.0f, 29.70f, 29.55f);
	vec3 endPos = vec3(0.0f, 89.23f, 29.55f);
	float weight = 0.0f;
	bool opening = false;

public:
	void Start() override;
	void Update(float deltaTime) override;

	void Reset();

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};