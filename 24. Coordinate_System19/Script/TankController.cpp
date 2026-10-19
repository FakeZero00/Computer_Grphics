#include "TankController.h"
#include "Object.h"
#include <gl/glm/glm.hpp>

void TankController::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void TankController::Update(float deltaTime) {
	inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyPressed(GLFW_KEY_UP)) {
		tr->Translate(0.0f, 0.0f, -moveSpeed * deltaTime, true);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_DOWN)) {
		tr->Translate(0.0f, 0.0f, moveSpeed * deltaTime, true);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT)) {
		tr->Translate(-moveSpeed * deltaTime, 0.0f, 0.0f, true);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_RIGHT)) {
		tr->Translate(moveSpeed * deltaTime, 0.0f, 0.0f, true);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyPressed(GLFW_KEY_Z)) {
		camTr->Translate(0.0f, 0.0f, moveSpeed * deltaTime, true);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_Z)) {
		camTr->Translate(0.0f, 0.0f, -moveSpeed * deltaTime, true);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyPressed(GLFW_KEY_X)) {
		camTr->Translate(-moveSpeed * deltaTime, 0.0f, 0.0f, true);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_X)) {
		camTr->Translate(moveSpeed * deltaTime, 0.0f, 0.0f, true);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyPressed(GLFW_KEY_Y)) {
		camTr->Rotate(0.0f, -90.0f * deltaTime, 0.0f);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_Y)) {
		camTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyPressed(GLFW_KEY_R)) {
		camArmTr->Rotate(0.0f, -90.0f * deltaTime, 0.0f);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_R)) {
		camArmTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
	}

	if (inputManager.GetKeyDown(GLFW_KEY_D)) {
		isDScaling = !isDScaling;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_T)) {
		isTRotating = !isTRotating;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_L)) {
		if (!isLMoving) {
			isLMoving = true;
			lWeight = 0.0f;
			lStartPos_L = TopTr_L->position;
			lEndPos_L = TopTr_R->position;
			lStartPos_R = TopTr_R->position;
			lEndPos_R = TopTr_L->position;
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_G)) {
		isGRotating = !isGRotating;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_P)) {
		isPRotating = !isPRotating;
	}

	if (isDScaling) {
		dWeight += deltaTime;
		if (dWeight > 1.0f) dWeight = 1.0f;
	}
	else {
		dWeight -= deltaTime;
		if (dWeight < 0.0f) dWeight = 0.0f;
	}

	vec3 startScale = vec3(1.0f, 1.0f, 1.0f);
	vec3 endScale = vec3(1.0f, 2.0f, 1.0f);
	vec3 currentScale = glm::mix(startScale, endScale, dWeight);

	BottomTr_L->SetLocalScale(currentScale.x, currentScale.y, currentScale.z);
	BottomTr_R->SetLocalScale(currentScale.x, currentScale.y, currentScale.z);

	vec3 startPos_L = vec3(0.88f, 0.28f, 0.0f);
	vec3 endPos_L = vec3(0.88f, 0.55f, 0.0f);
	vec3 currentPos_L = glm::mix(startPos_L, endPos_L, dWeight);

	vec3 startPos_R = vec3(-0.88f, 0.28f, 0.0f);
	vec3 endPos_R = vec3(-0.88f, 0.55f, 0.0f);
	vec3 currentPos_R = glm::mix(startPos_R, endPos_R, dWeight);

	BottomTr_L->SetLocalPosition(currentPos_L.x, currentPos_L.y, currentPos_L.z);
	BottomTr_R->SetLocalPosition(currentPos_R.x, currentPos_R.y, currentPos_R.z);

	vec3 startPos_M = vec3(0.0f, 0.76f, 0.0f);
	vec3 endPos_M = vec3(0.0f, 1.33f, 0.0f);
	vec3 currentPos_M = glm::mix(startPos_M, endPos_M, dWeight);

	MiddleTr->SetLocalPosition(currentPos_M.x, currentPos_M.y, currentPos_M.z);

	if (isTRotating) {
		MiddleTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
	}

	if (isLMoving) {
		lWeight += deltaTime;
		if (lWeight > 1.0f) {
			lWeight = 1.0f;
			isLMoving = false;
		}

		vec3 currentPos_L = glm::mix(lStartPos_L, lEndPos_L, lWeight);
		vec3 currentPos_R = glm::mix(lStartPos_R, lEndPos_R, lWeight);

		TopTr_L->SetLocalPosition(currentPos_L.x, currentPos_L.y, currentPos_L.z);
		TopTr_R->SetLocalPosition(currentPos_R.x, currentPos_R.y, currentPos_R.z);
	}

	if (isGRotating) {
		if (gRotFlag) {
			gWeight += deltaTime;
			if (gWeight > 1.0f) {
				gWeight = 1.0f;
				gRotFlag = false;
			}
		}
		else {
			gWeight -= deltaTime;
			if (gWeight < 0.0f) {
				gWeight = 0.0f;
				gRotFlag = true;
			}
		}

		quat currentRot_L = glm::slerp(gRotLQuat, gRotRQuat, gWeight);
		quat currentRot_R = glm::slerp(gRotRQuat, gRotLQuat, gWeight);

		BarrelTr_L->SetLocalRotation(currentRot_L);
		BarrelTr_R->SetLocalRotation(currentRot_R);
	}

	if (isPRotating) {
		if (isPRotating) {
			if (pRotFlag) {
				pWeight += deltaTime;
				if (pWeight > 1.0f) {
					pWeight = 1.0f;
					pRotFlag = false;
				}
			}
			else {
				pWeight -= deltaTime;
				if (pWeight < 0.0f) {
					pWeight = 0.0f;
					pRotFlag = true;
				}
			}

			quat currentRot_L = glm::slerp(pRotLQuat, pRotRQuat, pWeight);
			quat currentRot_R = glm::slerp(pRotRQuat, pRotLQuat, pWeight);
			FlagTr_L->SetLocalRotation(currentRot_L);
			FlagTr_R->SetLocalRotation(currentRot_R);
		}
	}
}

Component* TankController::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TankController* tankController = obj->AddComponent<TankController>();

	tankController->camArmTr = spawnedObjects.at(props["camArmTr"])->GetComponent<Transform>();
	tankController->camTr = spawnedObjects.at(props["camTr"])->GetComponent<Transform>();
	tankController->BottomTr_L = spawnedObjects.at(props["BottomTr_L"])->GetComponent<Transform>();
	tankController->BottomTr_R = spawnedObjects.at(props["BottomTr_R"])->GetComponent<Transform>();
	tankController->MiddleTr = spawnedObjects.at(props["MiddleTr"])->GetComponent<Transform>();
	tankController->TopTr_L = spawnedObjects.at(props["TopTr_L"])->GetComponent<Transform>();
	tankController->TopTr_R = spawnedObjects.at(props["TopTr_R"])->GetComponent<Transform>();
	tankController->BarrelTr_L = spawnedObjects.at(props["BarrelTr_L"])->GetComponent<Transform>();
	tankController->BarrelTr_R = spawnedObjects.at(props["BarrelTr_R"])->GetComponent<Transform>();
	tankController->FlagTr_L = spawnedObjects.at(props["FlagTr_L"])->GetComponent<Transform>();
	tankController->FlagTr_R = spawnedObjects.at(props["FlagTr_R"])->GetComponent<Transform>();

	return tankController;
}

REGISTER_COMPONENT(TankController);