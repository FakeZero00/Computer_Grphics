#pragma once
#include <vector>
#include "Component.h"
using namespace std;

class DirectorScript : public Component {
public:
	DirectorScript() = default;

	void Update(float deltaTime) override;

private:
	vector<Object*> Squares;
};