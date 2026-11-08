#pragma once
#include "Component.h"
#include "../AllComponent.h"
#include "Object.h"

class RobotController : public Component {
private:
	Transform* tr;
	RigidBody* rb;

	Object* ArmL;
	Object* ArmR;
	Object* LegL;
	Object* LegR;

	Transform* ArmLtr;
	Transform* ArmRtr;
	Transform* LegLtr;
	Transform* LegRtr;

	int moveMode = 0;
	bool movingBackward = false;
	float weight = 0.5f;

	float moveSpeed = 10.0f;
	float rotateAngle = 30.0f;
	float rotateSpeed = 1.5f;
	bool isGrounded = true;

public:
	void Start() override;
	void Update(float deltaTime) override;

	void OnTriggerEnter(Object* other) override;

	void Reset();

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};