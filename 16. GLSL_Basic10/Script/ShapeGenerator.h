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
	Mesh* rightPolyMesh;
	Mesh* rectMesh;

	vector<vec3> regularPolyCP;
	vector<vec3> rightPolyCP;
	vector<vec3> rectCP;
	
	vector<Object*> generatedObjects;
	vector<Object*> generatedColliders;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urdColor{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdPos{ -0.8f, 0.35f };
	uniform_real_distribution<float> urdPos2{ -0.8f, 0.8f };

	ShapeGenerator(Mesh* regularPolyMesh, Mesh* rightPolyMesh, Mesh* rectMesh,
			vector<vec3> regularPolyCP, vector<vec3> rightPolyCP, vector<vec3> rectCP) : regularPolyMesh(regularPolyMesh), rightPolyMesh(rightPolyMesh), rectMesh(rectMesh), regularPolyCP(regularPolyCP), rightPolyCP(rightPolyCP), rectCP(rectCP) {}

	Object* createShape(string name);
	void ResetShapes();

	void Start() override;
	void Update(float deltaTime) override;
};