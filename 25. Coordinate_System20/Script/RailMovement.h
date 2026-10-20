#pragma once
#include "Component.h"
#include "Transform.h"

class RailMovement : public Component {
private:
	Transform* tr;

	bool isMoving = false;

public:
	vec3 startPos1;
	vec3 endPos1;
	vec3 startPos2;
	vec3 endPos2;

	quat startQuat = quat(radians(vec3(0.0f, 0.0f, 0.0f)));
	vec3 endRot = vec3(0.0f, -90.0f, 0.0f);
	quat endQuat = quat(radians(endRot));

	float startWeight = 0.0f;
	float speed = 1.0f;
	float weight = 0.0f;

	void Start() override;
	void Update(float deltaTime) override;

	RailMovement() = default;
	RailMovement(float weight, vec3 startPos1, vec3 endPos1, vec3 startPos2, vec3 endPos2) : weight(weight), startPos1(startPos1), endPos1(endPos1), startPos2(startPos2), endPos2(endPos2) {}

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};