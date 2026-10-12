#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Object.h"
#include <vector>
#include <random>
#include <gl/glm/gtc/quaternion.hpp>
using namespace std;

class ObjectManagement : public Component {
public:
	bool isValid = true;

	map<string, Mesh*> meshes;
	map<string, Object*> objects;

	int scriptID;
	bool isDepthTestEnabled = true;
	bool isYRotating = false;
	bool isPYRotating = false;
	bool isMZRotating = false;
	float fWeight = 0.0f;
	bool isXRotating = false;
	bool isPZScaling = false;
	float bWeight = 0.0f;

	bool is1Rotating = false;
	string rotatingObjectName1[2];
	float rotatingAngle1 = 0.0f;

	bool is2Rotating = false;
	string rotatingObjectName2[2];
	quat startRot2[2];
	quat endRot2[2];
	float rotatingAngle2 = 0.0f;

	bool is4Rotating = false;
	bool is5Rotating = false;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_int_distribution<int> rand1{ 0, 3 };
	uniform_int_distribution<int> rand1_2{ 0, 1 };
	uniform_int_distribution<int> rand2{ 0, 5 };
	uniform_int_distribution<int> rand2_2{ 0, 3 };

	ObjectManagement(int scriptID, map<string, Mesh*> meshes) : scriptID(scriptID), meshes(meshes) {}

	void ResetObjects();

	void Start() override;
	void Update(float deltaTime) override;
};