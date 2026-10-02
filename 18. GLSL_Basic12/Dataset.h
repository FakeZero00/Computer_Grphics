#pragma once
#include <vector>
#include <gl/glm/glm.hpp>
#include "Vertex.h"
using namespace std;
using namespace glm;

vector<Vertex> isoPolyvert = {
	{ vec3(0.0f, 0.1f, 0.0f), vec3(0.0f) },
	{ vec3(-0.05f, -0.05f, 0.0f), vec3(0.0f) },
	{ vec3(0.05f, -0.05f, 0.0f), vec3(0.0f) },
};

vector<GLubyte> isoPolyidx = {
	0, 1, 2
};

vector<Vertex> rightPolyvert = {
	{ vec3(-0.1f, -0.2f, 0.0f), vec3(0.0f) },
	{ vec3(0.2f, -0.2f, 0.0f), vec3(0.0f) },
	{ vec3(-0.1f, 0.4f, 0.0f), vec3(0.0f) },
};

vector<GLubyte> rightPolyidx = {
	0, 1, 2
};

vector<vec3> rightPolyCP = {
	vec3(-0.1f, -0.2f, 0.0f),
	vec3(0.2f, -0.2f, 0.0f),
	vec3(-0.1f, 0.4f, 0.0f),
	vec3(-0.1f, -0.2f, 0.0f)
};

float lineLength = 0.03f;
vector<Vertex> regularPolyvert = {
	{ vec3(0.0f, lineLength * sqrt(3.0f) / 3.0f, 0.0f), vec3(0.0f)},
	{ vec3(lineLength / 2.0f, -lineLength * sqrt(3.0f) / 6.0f, 0.0f), vec3(0.0f) },
	{ vec3(-lineLength / 2.0f, -lineLength * sqrt(3.0f) / 6.0f, 0.0f), vec3(0.0f) }
};

vector<GLubyte> regularPolyidx = {
	0, 1, 2
};

vector<vec3> regularPolyCP = {
	vec3(0.0f, lineLength * sqrt(3.0f) / 3.0f, 0.0f),
	vec3(lineLength / 2.0f, -lineLength * sqrt(3.0f) / 6.0f, 0.0f),
	vec3(-lineLength / 2.0f, -lineLength * sqrt(3.0f) / 6.0f, 0.0f),
	vec3(0.0f, lineLength * sqrt(3.0f) / 3.0f, 0.0f)
};

vector<Vertex> rectvert = {
	{ vec3(-0.15f, 0.9f, 0.0f), vec3(0.0f) },
	{ vec3(-0.15f, -0.9f, 0.0f), vec3(0.0f) },
	{ vec3(0.15f, -0.9f, 0.0f), vec3(0.0f) },
	{ vec3(0.15f, 0.9f, 0.0f), vec3(0.0f) }
};

vector<Vertex> rectvert2 = {
	{ vec3(-0.13f, 0.1f, 0.0f), vec3(0.0f) },
	{ vec3(-0.13f, -0.1f, 0.0f), vec3(0.0f) },
	{ vec3(0.13f, -0.1f, 0.0f), vec3(0.0f) },
	{ vec3(0.13f, 0.1f, 0.0f), vec3(0.0f) }
};

vector<GLubyte> rectidx = {
	0, 1, 2,
	0, 2, 3
};

vector<vec3> rectCP = {
	vec3(-0.5f, 0.15f, 0.0f),
	vec3(-0.5f, -0.15f, 0.0f),
	vec3(0.5f, -0.15f, 0.0f),
	vec3(0.5f, 0.15f, 0.0f),
	vec3(-0.5f, 0.15f, 0.0f)
};