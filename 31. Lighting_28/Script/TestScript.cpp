#include "TestScript.h"
#include "Object.h"

void TestScript::Start() {
	tr = gameObject->GetComponent<Transform>();
	
	light = lightObj->GetComponent<Light>();
	lightRootTr = lightRoot->GetComponent<Transform>();

	inputManager = &gameObject->ctx.inputManager;
}

void TestScript::Update(float deltaTime) {
	if (inputManager->GetKeyDown(GLFW_KEY_M)) {
		if (isLight) {
			isLight = false;
			light->intensity = 0.1f;
		}
		else {
			isLight = true;
			light->intensity = 1.0f;
		}
	}

	if (inputManager->GetKeyDown(GLFW_KEY_C)) {
		currentColorIndex = (currentColorIndex + 1) % 3;
		light->lightColor = lightColor[currentColorIndex];
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager->GetKeyDown(GLFW_KEY_Y)) {
		isRYRotating = !isRYRotating;
	}
	else if (inputManager->GetKeyDown(GLFW_KEY_Y)) {
		isYRotating = !isYRotating;
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager->GetKeyDown(GLFW_KEY_R)) {
		isRRRotating = !isRRRotating;
	}
	else if (inputManager->GetKeyDown(GLFW_KEY_R)) {
		isRRotating = !isRRotating;
	}

	if (isYRotating) {
		lightRootTr->Rotate(0.0f, rotateSpeed * deltaTime, 0.0f);
	}
	if (isRYRotating) {
		lightRootTr->Rotate(0.0f, -rotateSpeed * deltaTime, 0.0f);
	}

	if (isRRotating) {
		tr->Rotate(0.0f, rotateSpeed * deltaTime, 0.0f);
	}
	if (isRRRotating) {
		tr->Rotate(0.0f, -rotateSpeed * deltaTime, 0.0f);
	}
}

Component* TestScript::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TestScript* testScript = obj->AddComponent<TestScript>();
	
	if (props.contains("lightObj")) testScript->lightObj = spawnedObjects.at(props["lightObj"]);
	if (props.contains("lightRootObj")) testScript->lightRoot = spawnedObjects.at(props["lightRootObj"]);

	return testScript;
}

REGISTER_COMPONENT(TestScript);