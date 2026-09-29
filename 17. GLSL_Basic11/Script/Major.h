#pragma once
#include "Component.h"
#include "Mesh.h"
#include <vector>
using namespace std;

class Major : public Component {
	bool isCollided = false;
	Object* otherObject = nullptr;
	
	vector<vec3> particleControlPoints{
		vec3(-0.01f, 0.01f, 0.0f),
		vec3(-0.01f, -0.01f, 0.0f),
		vec3(0.01f, -0.01f, 0.0f),
		vec3(0.01f, 0.01f, 0.0f),
		vec3(-0.01f, 0.01f, 0.0f)
	};

	void MakeParticle();
	void OnTriggerEnter(Object* other) override;
};