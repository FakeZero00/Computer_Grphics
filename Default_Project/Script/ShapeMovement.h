#pragma once
#include "Component.h"
#include <random>
#include <gl/glm/glm.hpp>
using namespace std;
using namespace glm;

class ShapeMovement : public Component {
public:
	int Movemode = 0;

	vec3 direction = vec3(0.0f, 0.0f, 0.0f);
	bool Timerbool = false;
	bool isCollided = false;
	bool isUp = true;
	bool isLeft = false;
	float zigTimer = 0.0f;

	Object* splineObj = nullptr;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urdDir{ -1.0f, 1.0f };
	uniform_real_distribution<float> urdDir2{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdDir3{ -0.5f, 0.5f };

	void OnTriggerEnter(Object* other) override;

	void Update(float deltaTime) override;
};