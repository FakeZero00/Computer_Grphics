#pragma once
#include <vector>
#include <gl/glew.h>
#include "Vertex.h"
using namespace std;
using namespace glm;

class Mesh {
public:
	GLuint VAO, VBO, EBO;
	GLsizei indexCount;

	vec3 minPos;
	vec3 maxPos;

	Mesh(const vector<Vertex>& vertices, const vector<GLubyte>& indices);
	void Bind() const;
};