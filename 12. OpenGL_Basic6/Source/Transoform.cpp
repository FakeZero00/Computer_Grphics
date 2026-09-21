#include "Transform.h"
#include "BoxCollider2D.h"
#include "Object.h"

Transform::Transform() {
	//초기 위치 설정
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;

	worldPosition.x = 0.0f;
	worldPosition.y = 0.0f;
	worldPosition.z = 0.0f;

	//초기 스케일 설정
	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;
}

void Transform::SetLocalPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;

	CalculateWorldPosition();
	if (gameObject->GetComponent<BoxCollider2D>())
		gameObject->GetComponent<BoxCollider2D>()->RecalculateCollision();
}

void Transform::CalculateWorldPosition() {
	if (parent != nullptr) {
		//부모가 있는 경우, 부모의 위치를 더함
		worldPosition.x = position.x + parent->position.x;
		worldPosition.y = position.y + parent->position.y;
		worldPosition.z = position.z + parent->position.z;
	}
	else {
		worldPosition.x = position.x;
		worldPosition.y = position.y;
		worldPosition.z = position.z;
	}
}

void Transform::SetParent(Transform* newParent) {
	parent = newParent;
	if (parent != nullptr) {
		//새로운 부모의 자식 벡터에 현재 오브젝트 추가
		parent->children.push_back(this);
	}
}