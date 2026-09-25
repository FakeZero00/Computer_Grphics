#pragma once
#include "Component.h"
#include <vector>
#include <gl/glm/glm.hpp>
#include <gl/glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

class Material;

class Spline : public Component {
	vector<vec3> controlPoints;
	vec3 Color;

	Spline(vector<vec3> controlPoints) : controlPoints(controlPoints) {}

	void Render() override;
};