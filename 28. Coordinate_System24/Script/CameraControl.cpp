#include "CameraControl.h"
#include "Object.h"

void CameraControl::Start() {
	cam = gameObject->GetComponent<Camera>();
}

void CameraControl::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyPressed(GLFW_KEY_KP_ADD)) {
		cam->fov -= 20.0f * deltaTime;
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
		cam->fov += 20.0f * deltaTime;
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT)){
		camArmTr->Rotate(0.0f, -90.0f * deltaTime, 0.0f, true);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_RIGHT)) {
		camArmTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
	}

	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyDown(GLFW_KEY_P)) {
		cam->isOrthographic = true;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_P)) {
		cam->isOrthographic = false;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		cam->fov = 60.0f;
		cam->isOrthographic = false;
		camArmTr->SetLocalRotation(0.0f, 0.0f, 0.0f);
		gameObject->GetComponent<Transform>()->SetLocalPosition(0.0f, 5.0f, 5.0f);
		gameObject->GetComponent<Transform>()->SetLocalRotation(45.0f, 180.0f, 0.0f);
	}
}

Component* CameraControl::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	CameraControl* cameraControl = obj->AddComponent<CameraControl>();

	cameraControl->camArmTr = spawnedObjects.at(props["camArmTr"])->GetComponent<Transform>();

	return cameraControl;
}

REGISTER_COMPONENT(CameraControl);