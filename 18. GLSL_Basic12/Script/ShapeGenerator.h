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
	float spawnPosL;

	Object* shapeR;
	float spawnPosR;

	vector<Object*> shapes;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urdColor{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdSpd{ 0.5f, 1.5f };

	ShapeGenerator(Mesh* rectMesh, float spawnPosL, float spawnPosR) : rectMesh(rectMesh), spawnPosL(spawnPosL), spawnPosR(spawnPosR) {}

	Object* createShape(string name, bool isLeft);

	void Start() override;
	void Update(float deltaTime) override;
};