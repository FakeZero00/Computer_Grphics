#pragma once
#include "Component.h"
#include "Mesh.h"
#include <random>
#include <vector>
#include "Object.h"
using namespace std;

class ShapeGenerator : public Component {
public:
	Mesh* rectMesh;

	Object* shapeL;
	vec3 spawnPosL;

	Object* shapeR;
	vec3 spawnPosR;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urdColor{ 0.0f, 1.0f };

	ShapeGenerator(Mesh* rectMesh, vec3 spawnPosL, vec3 spawnPosR) : rectMesh(rectMesh), spawnPosL(spawnPosL), spawnPosR(spawnPosR) {}

	Object* createShape(string name);

	void Start() override;
	void Update(float deltaTime) override;
};