#pragma once
#include "../AllComponent.h"
#include "Component.h"
#include "InputManager.h"
#include <random>

class TankController : public Component {
private:
	Transform* tr;
	InputManager inputManager;
	float moveSpeed = 5.0f;

	bool isDScaling = false;
	float dWeight = 0.0f;

	bool isTRotating = false;

	bool isLMoving = false;
	float lWeight = 0.0f;
	vec3 lStartPos_L = vec3{ 0.0f };
	vec3 lEndPos_L = vec3{ 0.0f };
	vec3 lStartPos_R = vec3{ 0.0f };
	vec3 lEndPos_R = vec3{ 0.0f };

	bool isGRotating = false;
	vec3 gRotL = vec3{ radians(0.0f), radians(90.0f), radians(0.0f) };
	quat gRotLQuat = quat{ gRotL };
	vec3 gRotR = vec3{ radians(0.0f), radians(-90.0f), radians(0.0f) };
	quat gRotRQuat = quat{ gRotR };
	float gWeight = 0.5f;
	bool gRotFlag = true;

	bool isPRotating = false;
	vec3 pRotL = vec3{ 90.0f, 0.0f, 0.0f };
	quat pRotLQuat = quat{ radians(pRotL) };
	vec3 pRotR = vec3{ -90.0f, 0.0f, 0.0f };
	quat pRotRQuat = quat{ radians(pRotR) };
	float pWeight = 0.5f;
	bool pRotFlag = true;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> colorUrd{ 0.0f, 1.0f };

public:
	Transform* camArmTr;
	Transform* camTr;
	Transform* BottomTr_L;
	Transform* BottomTr_R;
	Transform* MiddleTr;
	Transform* TopTr_L;
	Transform* TopTr_R;
	Transform* BarrelTr_L;
	Transform* BarrelTr_R;
	Transform* FlagTr_L;
	Transform* FlagTr_R;

	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};