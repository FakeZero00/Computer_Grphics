#pragma once
#include <vector>
#include <gl/glm/glm.hpp>
#include "Vertex.h"
using namespace std;
using namespace glm;

vector<vec3> controlPoints = {
	vec3(-1.0f, 0.0f, 0.0f),
	vec3(-0.5f, 1.0f, 0.0f),
	vec3(0.5f, -1.0f, 0.0f),
	vec3(1.0f, 0.0f, 0.0f)
};

vector<Vertex> isoPolyvert = {
	{ vec3(0.0f, 0.1f, 0.0f), vec3(0.0f) },
	{ vec3(-0.05f, -0.05f, 0.0f), vec3(0.0f) },
	{ vec3(0.05f, -0.05f, 0.0f), vec3(0.0f) },
};

vector<GLubyte> isoPolyidx = {
	0, 1, 2
};

vector<Vertex> Rectvert = {
	{ vec3(-0.1f, 0.1f, 0.0f), vec3(0.0f) },
	{ vec3(-0.1f, -0.1f, 0.0f), vec3(0.0f) },
	{ vec3(0.1f, -0.1f, 0.0f), vec3(0.0f) },
	{ vec3(0.1f, 0.1f, 0.0f), vec3(0.0f) }
};

vector<GLubyte> Rectidx = {
	0, 1, 2,
	0, 2, 3
};