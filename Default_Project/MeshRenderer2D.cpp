#include "MeshRenderer2D.h"
#include "Transform.h"
#include "Object.h"
#include <gl/glew.h>

MeshRenderer2D::MeshRenderer2D() {
	//초기 위치 설정
	minPos.x = 0.0f;
	minPos.y = 0.0f;
	maxPos.x = 1.0f;
	maxPos.y = 1.0f;

	//초기 크기 설정
	width = (maxPos.x - minPos.x);
	height = (maxPos.y - minPos.y);
}

MeshRenderer2D::MeshRenderer2D(float width, float height, Color color) {
	//크기 설정
	this->width = width;
	this->height = height;
	this->color = color;
}

void  MeshRenderer2D::SetSize(float width, float height) {
	this->width = width;
	this->height = height;
}

void MeshRenderer2D::Render() {
	Transform* transform = gameObject->GetComponent<Transform>();
	if (transform == nullptr) return;

	float scaledWidth = width * transform->scale.x;
	float scaledHeight = height * transform->scale.y;

	//사각형 그리기
	minPos.x = transform->position.x - scaledWidth / 2.0f;
	minPos.y = transform->position.y - scaledHeight / 2.0f;
	maxPos.x = transform->position.x + scaledWidth / 2.0f;
	maxPos.y = transform->position.y + scaledHeight / 2.0f;

	//색상 설정
	glColor4f(color.r, color.g, color.b, color.a);

	glRectf(minPos.x, minPos.y, maxPos.x, maxPos.y);
}