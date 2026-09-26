#pragma once
#include "Component.h"
#include "Mesh.h"
#include <random>
#include <vector>
#include "Object.h"
using namespace std;

class ShapeGenerator : public Component {
public:
	Mesh* isoPolyMesh;
	Mesh* rectMesh;

	vector<Object*> generatedObjects;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ -1.0f, 1.0f };
	uniform_real_distribution<float> urdLine{ -0.3f, 0.3f };
	uniform_real_distribution<float> urdColor{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdScale{ 0.8f, 1.2f };

	ShapeGenerator(Mesh* isoPolyMesh, Mesh* rectMesh) : isoPolyMesh(isoPolyMesh), rectMesh(rectMesh) {}

	void Update(float deltaTime) override;
};