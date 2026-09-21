#pragma once
#include <vector>
#include "Component.h"
using namespace std;

struct Position {
	float x;
	float y;
	float z;
};

struct Scale {
	float x;
	float y;
	float z;
};

class Transform : public Component {
public:
	Position position;
	Position worldPosition;
	Scale scale;

	Transform* parent = nullptr;
	vector<Transform*> children = vector<Transform*>{}; //빈 자식 벡터 생성

	Transform();
	
	void SetLocalPosition(float x, float y, float z);
	void Translate(float x, float y, float z);
	void CalculateWorldPosition();
	void SetParent(Transform* newParent);
};