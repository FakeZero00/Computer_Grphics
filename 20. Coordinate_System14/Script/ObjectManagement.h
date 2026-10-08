#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Object.h"
#include <vector>
#include <random>
using namespace std;

class ObjectManagement : public Component {
private:
	float speed = 100.0f;
	float moveSpeed = 5.0f;

	int isXRotation = 0;	//0: 회전 없음, 1: 양의 방향 회전, -1: 음의 방향 회전
	int isYRotation = 0;	//0: 회전 없음, 1: 양의 방향 회전, -1: 음의 방향 회전


public:
	Object* cube;
	Object* pyramid;

	bool isDepthTest = true;

	ObjectManagement(Object* cube, Object* pyramid) : cube(cube), pyramid(pyramid) {}

	void Start() override;
	void Update(float deltaTime) override;
};
