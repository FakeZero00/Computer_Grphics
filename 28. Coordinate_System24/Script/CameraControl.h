#pragma once
#include "Component.h"
#include "Camera.h"
#include "Object.h"
#include "Transform.h"

class CameraControl : public Component {
private:
	Transform* tr;

	Object* railGenerator;
	Transform* railGeneratorTr;

	Object* Cube1 = nullptr;
	Object* Cube2 = nullptr;
	Object* Cube3 = nullptr;
	Object* Cube4 = nullptr;
	Object* Cube5 = nullptr;

	Transform* Cube1Tr;
	Transform* Cube2Tr;
	Transform* Cube3Tr;
	Transform* Cube4Tr;
	Transform* Cube5Tr;

	bool isFPS = false;
	int cubeNum = 0;

public:
	Camera* cam;
	Transform* camArmTr;

	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};