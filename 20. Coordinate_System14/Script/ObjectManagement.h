#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Object.h"
#include <vector>
#include <random>
using namespace std;

class ObjectManagement : public Component {
public:
	vector <Mesh*> meshes;
	vector <Object*> objects;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_int_distribution<int> randCube{ 0, 5 };
	uniform_int_distribution<int> randTri{ 6, 9 };

	ObjectManagement(vector<Mesh*> meshes) : meshes(meshes) {}

	void AllDisable();

	void Start() override;
	void Update(float deltaTime) override;
};
