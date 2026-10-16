#include "TankController.h"
#include "Object.h"
#include <gl/glm/glm.hpp>

void TankController::Start() {
	cout << "TankController Start" << endl;
	tr = gameObject->GetComponent<Transform>();
}

void TankController::Update(float deltaTime) {
	inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyPressed(GLFW_KEY_UP)) {
		cout << "Up key pressed" << endl;
		tr->Translate(0.0f, 0.0f, -moveSpeed * deltaTime);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_DOWN)) {
		tr->Translate(0.0f, 0.0f, moveSpeed * deltaTime);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT)) {
		tr->Translate(-moveSpeed * deltaTime, 0.0f, 0.0f);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_RIGHT)) {
		tr->Translate(moveSpeed * deltaTime, 0.0f, 0.0f);
	}

	if (inputManager.GetKeyDown(GLFW_KEY_D)) {
		isDScaling = !isDScaling;
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
}

Component* TankController::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TankController* tankController = obj->AddComponent<TankController>();

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