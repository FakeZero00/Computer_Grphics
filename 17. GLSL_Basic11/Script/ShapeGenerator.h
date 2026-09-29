#pragma once
#include "Component.h"
#include "Mesh.h"
#include <random>
#include <vector>
#include "Object.h"
using namespace std;

class ShapeGenerator : public Component {
public:
	Mesh* regularPolyMesh;
	Mesh* rectMesh;

	int horizontal;
	int vertical;
	float centerOffsetX = 0.0f;
	float centerOffsetY = 0.0f;

	vector<vector<Object*>> board;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urdColor{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdScale{ 1.0f, 4.0f };
	uniform_real_distribution<float> urdScaleRect{ 1.0f, 1.3f };

	ShapeGenerator(Mesh* regularPolyMesh, Mesh* rectMesh, int horizontal, int vertical) : regularPolyMesh(regularPolyMesh), rectMesh(rectMesh), horizontal(horizontal), vertical(vertical) {}

	Object* createShape(string name, int x, int y);
	void ResetShapes();

	void Start() override;
	void Update(float deltaTime) override;
};