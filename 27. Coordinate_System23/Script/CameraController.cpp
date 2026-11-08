#include "CameraController.h"
#include "Object.h"

void CameraController::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void CameraController::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) && inputManager.GetKeyPressed(GLFW_KEY_Z)) {
		camTr->Translate(0.0f, 0.0f, moveSpeed * deltaTime);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_Z)) {
		camTr->Translate(0.0f, 0.0f, -moveSpeed * deltaTime);
	}

	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) && inputManager.GetKeyPressed(GLFW_KEY_X)) {
		camTr->Translate(moveSpeed * deltaTime, 0.0f, 0.0f);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_X)) {
		camTr->Translate(-moveSpeed * deltaTime, 0.0f, 0.0f);
	}

	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) && inputManager.GetKeyPressed(GLFW_KEY_Y)) {
		tr->Rotate(0.0f, rotateSpeed * deltaTime, 0.0f);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_Y)) {
		tr->Rotate(0.0f, -rotateSpeed * deltaTime, 0.0f);
	}

	if (inputManager.GetKeyDown(GLFW_KEY_I)) Reset();
}

void CameraController::Reset() {
	tr->SetLocalPosition(0.0f, 0.0f, 0.0f);
	tr->SetLocalRotation(0.0f, 0.0f, 0.0f);

	camTr->SetLocalPosition(0.0f, 50.0f, 90.0f);
	camTr->SetLocalRotation(15.0f, 180.0f, 0.0f);
}

Component* CameraController::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	CameraController* cameraController = obj->AddComponent<CameraController>();

	if (props.contains("camTr")) cameraController->camTr = spawnedObjects.at(props["camTr"])->GetComponent<Transform>();

	return cameraController;
}

REGISTER_COMPONENT(CameraController);