#pragma once
#include "Component.h"
#include "../AllComponent.h"
#include "Object.h"

class CameraController : public Component {
private:
	Transform* tr;
	Transform* camTr;

	float moveSpeed = 20.0f;
	float rotateSpeed = 90.0f;

public:
	void Start() override;
	void Update(float deltaTime) override;

	void Reset();

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};