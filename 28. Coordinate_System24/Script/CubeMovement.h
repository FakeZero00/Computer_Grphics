#pragma once
#include "Component.h"
#include "Transform.h"

class CubeMovement : public Component {
private:
	Transform* tr;

	int number;
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
	float truckWeight = 0.0f;

	bool isLoaded = false;
	Transform* loadedDestTr;
	float loadTotalLen;
	float loadWeight = 0.0f;
	float loadSpeed = 5.0f;
	vec3 loadedStartPos;

	void Start() override;
	void Update(float deltaTime) override;

	void Load2Truck(Transform* destObjTr);

	CubeMovement() = default;
	CubeMovement(int number, float weight, vec3 startPos1, vec3 endPos1, vec3 startPos2, vec3 endPos2) : number(number), weight(weight), startPos1(startPos1), endPos1(endPos1), startPos2(startPos2), endPos2(endPos2) {}

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};