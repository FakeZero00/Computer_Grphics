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
	vector<vec3> isoPolyvert;

	bool isLineMode = false;

	Object* obj1[2];
	Object* obj2[2];
	Object* obj3[2];
	Object* obj4[2];

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urdColor{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdScale{ 1.0f, 2.0f };

	ShapeGenerator(Mesh* isoPolyMesh, vector<vec3> isoPolyvert) : isoPolyMesh(isoPolyMesh), isoPolyvert(isoPolyvert) {}

	void Start() override;
	void Update(float deltaTime) override;
};