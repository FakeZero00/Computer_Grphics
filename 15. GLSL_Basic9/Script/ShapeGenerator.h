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
	
	vector<Object*> generatedObjects;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urdColor{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdScale{ 1.0f, 2.0f };

	ShapeGenerator(Mesh* isoPolyMesh) : isoPolyMesh(isoPolyMesh) {}

	void Update(float deltaTime) override;
};