#include "BoxController.h"
#include "Object.h"

void BoxController::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void BoxController::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		currentMousePos = inputManager.GetMouseX();
	}
	else if (inputManager.GetKeyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		lastMousePos = currentMousePos;
		currentMousePos = inputManager.GetMouseX();
		float delta = currentMousePos - lastMousePos;
		tr->Rotate(0.0f, 0.0f, rotationSpeed * delta * 0.5f, true);
	}
}

Component* BoxController::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	BoxController* boxController = obj->AddComponent<BoxController>();

	return boxController;
}

REGISTER_COMPONENT(BoxController);