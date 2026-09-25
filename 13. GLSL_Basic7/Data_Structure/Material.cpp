#include "Material.h"

void Material::Use() {
	glUseProgram(shaderProgram);

	// 1. 저장된 int 값들을 셰이더의 uniform으로 일괄 전송
	for (const auto& pair : intUniforms) {
		GLint intLoc = glGetUniformLocation(shaderProgram, pair.first.c_str());
		if (intLoc == -1) continue;
		glUniform1i(intLoc, pair.second);
	}

	// 2. 저장된 float 값들을 셰이더의 uniform으로 일괄 전송
	for (const auto& pair : floatUniforms) {
		GLint floatLoc = glGetUniformLocation(shaderProgram, pair.first.c_str());
		if (floatLoc == -1) continue;
		glUniform1f(floatLoc, pair.second);
	}

	// 3. 저장된 vec3 값들을 셰이더의 uniform으로 일괄 전송
	for (const auto& pair : vec3Uniforms) {
		GLint vec3Loc = glGetUniformLocation(shaderProgram, pair.first.c_str());
		if (vec3Loc == -1) continue;
		glUniform3f(vec3Loc, pair.second.x, pair.second.y, pair.second.z);
	}

	//4. 저장된 vec4 값들을 셰이더의 uniform으로 일괄 전송
	for (const auto& pair : vec4Uniforms) {
		GLint vec4Loc = glGetUniformLocation(shaderProgram, pair.first.c_str());
		if (vec4Loc == -1) continue;
		glUniform4f(vec4Loc, pair.second.x, pair.second.y, pair.second.z, pair.second.w);
	}
}

void Material::SetInt(const string& name, int value) {
	intUniforms[name] = value;
}

void Material::SetFloat(const string& name, float value) {
	floatUniforms[name] = value;
}

void Material::SetVec3(const string& name, const vec3& value) {
	vec3Uniforms[name] = value;
}

void Material::SetVec4(const string& name, const vec4& value) {
	vec4Uniforms[name] = value;
}