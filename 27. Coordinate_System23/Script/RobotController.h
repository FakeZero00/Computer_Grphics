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

	vec3 startRotL = vec3(-30.0f, 0.0f, 0.0f);
	quat qStartRotL = quat{ radians(startRotL) };
	vec3 lastRotL = vec3(30.0f, 0.0f, 0.0f);
	quat qLastRotL = quat{ radians(lastRotL) };

	vec3 startRotR = -startRotL;
	quat qStartRotR = quat{ radians(startRotR) };
	vec3 lastRotR = -lastRotL;
	quat qLastRotR = quat{ radians(lastRotR) };

	float weight = 0.5f;

public:
	void Start() override;
	void Update(float deltaTime) override;

	void OnTriggerStay(Object* other) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};