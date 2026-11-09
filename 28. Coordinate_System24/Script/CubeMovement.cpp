#include "CubeMovement.h"
#include "Object.h"

void CubeMovement::Start() {
	tr = gameObject->GetComponent<Transform>();
	startWeight = weight;
}

void CubeMovement::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_B)) {
		isMoving = !isMoving;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		isMoving = false;
		weight = startWeight;
		isLoaded = false;
	}

	if (isLoaded) {
		loadWeight += loadSpeed * deltaTime;
		if (loadWeight >= loadTotalLen) {
			loadWeight = loadTotalLen;
		}
	}
	else {
		if (isMoving) {
			// 매 프레임 일정 속도(m/s)로 weight 증가
			weight += speed * deltaTime;
		}
	}

	if (!isLoaded) {
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
	else {
		vec3 middlePos = (loadedStartPos + loadedDestTr->worldPosition) * 0.5f + vec3{0.0f, 2.0f, 0.0f};
		float len1 = glm::distance(loadedStartPos, middlePos);
		float len2 = glm::distance(middlePos, loadedDestTr->worldPosition);
		loadTotalLen = len1 + len2;

		//전체 루프
		loadWeight = std::min(loadWeight, loadTotalLen);

		if (loadWeight <= len1) {
			float t = loadWeight / len1; // 0.0 ~ 1.0 정규화
			vec3 currentPos = glm::mix(loadedStartPos, middlePos, t);
			tr->SetLocalPosition(currentPos);
		}
		else if (loadWeight <= len1 + len2) {
			float t = (loadWeight - len1) / len2; // 0.0 ~ 1.0 정규화
			vec3 currentPos = glm::mix(middlePos, loadedDestTr->worldPosition, t);
			tr->SetLocalPosition(currentPos);
		}
	}
}

void CubeMovement::Load2Truck(Transform* destObjTr) {
	isLoaded = true;
	loadedDestTr = destObjTr;
	loadWeight = 0.0f;
	loadedStartPos = tr->position;
	tr->SetLocalRotation(0.0f, 0.0f, 0.0f);
}

Component* CubeMovement::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	CubeMovement* cubeMovement = obj->AddComponent<CubeMovement>();

	return cubeMovement;
}

REGISTER_COMPONENT(CubeMovement)