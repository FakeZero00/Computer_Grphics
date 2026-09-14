#include "Transform.h"

Transform::Transform() {
	//초기 위치 설정
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	//초기 스케일 설정
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;
}

void Transform::SetLocalPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

void Transform::SetParent(Transform* newParent) {
	parent = newParent;
	if (parent != nullptr) {
		//새로운 부모의 자식 벡터에 현재 오브젝트 추가
		parent->children.push_back(this);
	}
}