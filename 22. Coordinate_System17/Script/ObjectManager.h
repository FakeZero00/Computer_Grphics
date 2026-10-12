#pragma once
#include "Component.h"
#include "Mesh.h"
#include <vector>
#include <random>
#include <gl/glm/glm.hpp>
using namespace std;
using namespace glm;

class ObjectManager : public Component {
public:
	vector<Mesh*> meshes; // 관리할 Mesh 객체들의 벡터

	ObjectManager(vector<Mesh*> meshes) : meshes(meshes) {}

	Object* childL = nullptr;
	Object* childR = nullptr;

	vec3 childLPos = vec3(0.0f, 0.0f, 0.0f);
	vec3 childRPos = vec3(0.0f, 0.0f, 0.0f);

	int commandMode = 0;

	int isXRotatingL = 0;
	int isXRotatingR = 0;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_int_distribution<int> uid{ 0, 3 };
	uniform_real_distribution<float> ufdL{ 8.0f, 10.0f };
	uniform_real_distribution<float> ufdR{ -10.0f, -8.0f };

	void Update(float deltaTime) override;
};
