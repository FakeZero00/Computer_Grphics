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
	vec3 targetPosL = vec3(0.0f, 0.0f, 0.0f);
	vec3 childRPos = vec3(0.0f, 0.0f, 0.0f);
	vec3 targetPosR = vec3(0.0f, 0.0f, 0.0f);

	int commandMode = 0;

	int isXRotatingL = 0;
	int isXRotatingR = 0;
	int isYRotatingL = 0;
	int isYRotatingR = 0;

	int isRRotatingL = 0;
	int isRRotatingR = 0;
	int isAScalingL = 0;
	int isAScalingR = 0;
	int isBScalingL = 0;
	int isBScalingR = 0;
	int isDMovingL = 0;
	int isDMovingR = 0;
	int isEMovingL = 0;
	int isEMovingR = 0;

	int istMovingL = 0;
	float tMovingL = 0.0f;
	int istMovingR = 0;
	float tMovingR = 0.0f;

	bool isVMoving = false;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_int_distribution<int> uid{ 0, 3 };
	uniform_real_distribution<float> ufdL{ 7.0f, 9.0f };
	uniform_real_distribution<float> ufdR{ -9.0f, -7.0f };

	void ResetAll();

	void Update(float deltaTime) override;
};
