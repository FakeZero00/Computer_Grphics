#pragma once
#include "Component.h"
#include <vector>
using namespace std;

class SquareGenerator : public Component {
public:
	float width = 0.2f;
	float height = 0.2f;

	vector<pair<float, float>> positions;

	SquareGenerator() = default;

	void CreateSquare();

	void Update(float deltaTime) override;
};