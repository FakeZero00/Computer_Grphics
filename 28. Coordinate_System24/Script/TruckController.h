#pragma once
#include "Component.h"
#include "Object.h"
#include "Transform.h"

#include "CubeMovement.h"

class TruckController : public Component {
private:
	Transform* tr;

	Object* railGenerator;
	Transform* railGeneratorTr;

	Object* Cube1 = nullptr;
	Object* Cube2 = nullptr;
	Object* Cube3 = nullptr;
	Object* Cube4 = nullptr;
	Object* Cube5 = nullptr;

	CubeMovement* cube1Movement = nullptr;
	CubeMovement* cube2Movement = nullptr;
	CubeMovement* cube3Movement = nullptr;
	CubeMovement* cube4Movement = nullptr;
	CubeMovement* cube5Movement = nullptr;

	Transform* truckCube1;
	Transform* truckCube2;
	Transform* truckCube3;
	Transform* truckCube4;
	Transform* truckCube5;

	vec3 startPos = vec3{ -4.01f, 0.0f, -1.15f };
	vec3 endPos = vec3{ -4.01f, 0.0f, 5.29f };
	bool isMove = false;
	float moveWeight = 0.0f;
	float moveSpeed = 1.0f;

public:

	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};