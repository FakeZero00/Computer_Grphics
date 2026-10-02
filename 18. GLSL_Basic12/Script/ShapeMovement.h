#pragma once
#include "Component.h"
#include <random>
#include <gl/glm/glm.hpp>
using namespace std;
using namespace glm;

class ShapeMovement : public Component {
public:
	float speed = 20.0f;

	void Update(float deltaTime) override;
};