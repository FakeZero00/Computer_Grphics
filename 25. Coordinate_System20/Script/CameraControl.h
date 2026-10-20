#pragma once
#include "Component.h"
#include "Camera.h"
#include "Transform.h"

class CameraControl : public Component {

public:
	Camera* cam;
	Transform* camArmTr;

	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};