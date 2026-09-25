#include "Spline.h"
#include <map>
#include <string>
#include <gl/glew.h>
#include <gl/glm/gtc/type_ptr.hpp>
using namespace std;

//main에서 선언된 shaders 맵을 extern으로 참조
extern map<string, GLuint> shaders;

Spline::Spline(vector<vec3> controlPoints, vec4 color) : controlPoints(controlPoints), color(color) {
	InitDebugRender();
}

void Spline::Render() {
	GLuint splineShader = shaders["Spline"];
	glUseProgram(splineShader);

	//controlPoints는 이미 월드 좌표이므로 모델 변환 행렬을 단위 행렬(Identity)로 덮어씌움
	GLuint modelLoc = glGetUniformLocation(splineShader, "model");
	mat4 identity = mat4{ 1.0f };
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(identity));

	//Color를 셰이더에 전달
	GLuint colorLoc = glGetUniformLocation(splineShader, "color");
	glUniform4fv(colorLoc, 1, value_ptr(color));

	//controlPoints를 VBO에 업데이트
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, controlPoints.size() * 3 * sizeof(float), controlPoints.data());

	//Spline 그리기
	glDrawArrays(GL_LINE_STRIP, 0, controlPoints.size());
	glBindVertexArray(0);
}

void Spline::InitDebugRender() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, controlPoints.size() * 3 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Spline::SetColor(vec4 newColor) {
	color = newColor;
}