#pragma once
#include "Component.h"
#include <random>
#include <gl/glm/glm.hpp>
using namespace std;
using namespace glm;

class ShapeMovement : public Component {
public:
	bool isMoving = false;

	void Update(float deltaTime) override;
};