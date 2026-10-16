#pragma once
#include "../AllComponent.h"
#include "Component.h"
#include "InputManager.h"

class TankController : public Component {
private:
	Transform* tr;
	InputManager inputManager;
	float moveSpeed = 5.0f;

	bool isDScaling = false;
	float dWeight = 0.0f;

public:
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