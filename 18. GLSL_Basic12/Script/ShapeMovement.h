#pragma once
#include "Component.h"
#include <random>
#include <gl/glm/glm.hpp>
using namespace std;
using namespace glm;

class ShapeMovement : public Component {
public:
	float speed = 10.0f;
	float direction = 1.0f;

	bool isMove = true;
	bool isBorder = false;
	bool isEnter = false;

	vec3 destPos = vec3{ 0.0f, 0.0f, 0.0f };

	ShapeMovement(float speed, float direction) : speed(speed), direction(direction) {}

	void Update(float deltaTime) override;

	void OnTriggerEnter(Object* other) override;
	void OnTriggerExit(Object* other) override;
};