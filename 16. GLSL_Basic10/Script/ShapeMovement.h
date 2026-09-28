#pragma once
#include "Component.h"
#include <random>
#include <gl/glm/glm.hpp>
using namespace std;
using namespace glm;

class ShapeGenerator;

class ShapeMovement : public Component {
public:
	bool isMoving = false;

	ShapeGenerator* shapeGenerator;

	ShapeMovement(ShapeGenerator* shapeGenerator) : shapeGenerator(shapeGenerator) {}

	void SafeDestroy();

	void OnTriggerStay(Object* other) override;

	void Update(float deltaTime) override;
};