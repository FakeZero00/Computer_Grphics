#include "RailMovement.h"
#include "Object.h"

void RailMovement::Start() {
	tr = gameObject->GetComponent<Transform>();
	startWeight = weight;
}

void RailMovement::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_B)) {
		isMoving = !isMoving;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		isMoving = false;
		weight = startWeight;
	}

	if (isMoving) {
		// 매 프레임 일정 속도(m/s)로 weight 증가
		weight += speed * deltaTime;
	}

	// 각 구간의 실제 거리 계산
	float len1 = glm::distance(startPos1, endPos1);
	float len2 = 1.5f; // 회전 구간의 궤적 길이 (간격 보면서 미세조정 가능)
	float len3 = glm::distance(startPos2, endPos2);
	float totalLen = len1 + len2 + len3;

	// 전체 루프 (0.0 ~ totalLen)
	weight = fmod(weight, totalLen);

	// 1. 직선 1 구간 (0 ~ len1)
	if (weight <= len1) {
		float t = weight / len1; // 0.0 ~ 1.0 정규화
		vec3 currentPos = glm::mix(startPos1, endPos1, t);
		tr->SetLocalPosition(currentPos);
		tr->SetLocalRotation(startQuat);
	}
	// 2. 회전 구간 (len1 ~ len1 + len2)
	else if (weight <= len1 + len2) {
		float t = (weight - len1) / len2; // 0.0 ~ 1.0 정규화
		quat currentRot = glm::slerp(startQuat, endQuat, t);
		tr->SetLocalPosition(endPos1);
		tr->SetLocalRotation(currentRot);
	}
	// 3. 직선 2 구간 (len1 + len2 ~ totalLen)
	else {
		float t = (weight - (len1 + len2)) / len3; // 0.0 ~ 1.0 정규화
		vec3 currentPos = glm::mix(startPos2, endPos2, t);
		tr->SetLocalPosition(currentPos);
		tr->SetLocalRotation(endQuat);
	}
}

Component* RailMovement::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	RailMovement* railMovement = obj->AddComponent<RailMovement>();

	return railMovement;
}

REGISTER_COMPONENT(RailMovement)