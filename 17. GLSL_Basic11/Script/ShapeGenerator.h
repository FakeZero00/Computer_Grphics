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
	int finalPos[2] = { 0, 0 };

	vector<vector<Object*>> board;

	Object* major;
	int majorPos[2] = { 0, 0 };
	int direction[2] = { 1, 0 };
	int currentDirX = 1;
	float defaultCooltime = 1.0f;
	float cooltime = 1.0f;
	bool isStart = false;
	bool isDown = false;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urdColor{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdScale{ 1.0f, 4.0f };
	uniform_real_distribution<float> urdScaleRect{ 1.0f, 1.3f };

	ShapeGenerator(Mesh* regularPolyMesh, Mesh* rectMesh, int horizontal, int vertical) : regularPolyMesh(regularPolyMesh), rectMesh(rectMesh), horizontal(horizontal), vertical(vertical) {}

	Object* createShape(string name, int x, int y);
	void Move(int x, int y);

	void Start() override;
	void Update(float deltaTime) override;
};