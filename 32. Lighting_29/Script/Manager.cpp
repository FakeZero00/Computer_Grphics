#include "Manager.h"

void Manager::Start() {
	lightArmTf = lightArm->GetComponent<Transform>();

	lightTf = lightObj->GetComponent<Transform>();
	light = lightObj->GetComponent<Light>();

	inputManager = &gameObject->ctx.inputManager;
}

void Manager::Update(float deltaTime) {
	if (inputManager->GetKeyPressed(GLFW_KEY_R)) {
		lightArmTf->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_N)) {
		lightTf->Translate(0.0f, 0.0f, 3.0f * deltaTime);
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_F)) {
		lightTf->Translate(0.0f, 0.0f, -3.0f * deltaTime);
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_KP_ADD)) {
		light->intensity += 0.5f * deltaTime;
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
		light->intensity -= 0.5f * deltaTime;
	}
}

Component* Manager::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	Manager* script = obj->AddComponent<Manager>();

	if (props.contains("lightArm")) script->lightArm = spawnedObjects.at(props["lightArm"]);
	if (props.contains("lightObj")) script->lightObj = spawnedObjects.at(props["lightObj"]);

	return script;
}

REGISTER_COMPONENT(Manager);