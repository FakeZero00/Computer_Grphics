#pragma once
#include "Component.h"
#include "../AllComponent.h"
#include <random>

class BallMovement : public Component {
private:
	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ -5.0f, 5.0f };

	Transform* tr;
	vec3 velocity;
	float radius = 1.0f;

public:
	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};