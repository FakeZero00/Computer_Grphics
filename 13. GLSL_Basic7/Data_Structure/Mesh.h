#pragma once
#include <gl/glew.h>
#include <gl/glm/glm.hpp>
using namespace glm;

class Mesh {
public:
	GLuint VAO, VBO, EBO;
	GLsizei indexCount;

	vec3 minPos;
	vec3 max3Pos;

	Mesh(const float* vertices, GLsizeiptr vertSize, const GLubyte* indices, GLsizeiptr indexSize);
	void Bind() const;
};