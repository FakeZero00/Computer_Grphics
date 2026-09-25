#pragma once
#include "Component.h"
#include <vector>
#include <gl/glm/glm.hpp>
#include <gl/glew.h>
#include <gl/glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

class Spline : public Component {
public:
	vector<vec3> controlPoints;
	vec4 color;

	GLuint VAO = 0, VBO = 0;

	Spline(vector<vec3> controlPoints, vec4 color = vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

	void InitDebugRender();
	void SetColor(vec4 newColor);

	void Render() override;
};