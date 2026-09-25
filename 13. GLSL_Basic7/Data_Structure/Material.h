#pragma once
#include <map>
#include <string>
#include <gl/glew.h>
#include <gl/glm/glm.hpp>
using namespace std;
using namespace glm;

class Material {
public:
	GLuint shaderProgram;

	//타입별 Uniform 변수 저장 map
	map<string, int> intUniforms;
	map<string, float> floatUniforms;
	map<string, vec3> vec3Uniforms;
	map<string, vec4> vec4Uniforms;

	Material(GLuint programID) : shaderProgram(programID) {}

	void Use();

	void SetInt(const string& name, int value);
	void SetFloat(const string& name, float value);
	void SetVec3(const string& name, const vec3& value);
	void SetVec4(const string& name, const vec4& value);
};