#include "Spline.h"
#include <map>
#include <string>
#include <gl/glew.h>
#include <gl/glm/gtc/type_ptr.hpp>
#include "Object.h"
#include "Transform.h"
using namespace std;

//main에서 선언된 shaders 맵을 extern으로 참조
extern map<string, GLuint> shaders;

Spline::Spline(vector<vec3> controlPoints, vec4 color) : controlPoints(controlPoints), color(color) {
	InitRender();
}

void Spline::Render() {
	GLuint splineShader = shaders["Spline"];
	glUseProgram(splineShader);

	//controlPoints의 월드 좌표 계산을 위해 model 행렬을 셰이더에 전달
	GLuint modelLoc = glGetUniformLocation(splineShader, "model");
	Transform* tr = gameObject->GetComponent<Transform>();

	mat4 localMatrix = mat4{ 1.0f };
	localMatrix = translate(localMatrix, tr->position);
	localMatrix *= mat4_cast(tr->rotation);
	localMatrix = glm::scale(localMatrix, tr->scale);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(localMatrix));

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

void Spline::InitRender() {
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