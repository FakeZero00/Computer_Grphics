#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Object.h"
#include <vector>
#include <random>
#include <gl/glm/gtc/quaternion.hpp>
using namespace std;

class PyramidController : public Component {
public:
	map<string, Mesh*> meshes;
	vector<Object*> objects;

	Object* floorObject;

	bool is6Move = false;
	bool is6Rotating = false;
	float weight6 = 0.0f;

	bool is7Move = false;
	bool is7Rotating = false;
	float weight7[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_int_distribution<int> rand1{ 0, 3 };

	PyramidController(map<string, Mesh*> meshes) : meshes(meshes) {}

	void ResetObjects();

	void Start() override;
	void Update(float deltaTime) override;
};