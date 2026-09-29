#pragma once
#include "Component.h"
#include <random>
#include <gl/glm/glm.hpp>
using namespace std;
using namespace glm;

class ShapeGenerator;

class ShapeMovement : public Component {
public:
	void Update(float deltaTime) override;
};