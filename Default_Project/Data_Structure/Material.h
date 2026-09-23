#pragma once
#include <gl/glew.h>

class Material {
public:
	GLuint shaderProgram;

	Material(GLuint programID) : shaderProgram(programID) {}

	void Use() {
		glUseProgram(shaderProgram);
	}

	// 예시: 색상 파라미터 제어 함수
	// void SetColor(const std::string& name, float r, float g, float b) { ... }
};