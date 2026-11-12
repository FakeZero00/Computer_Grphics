#include "TestScript.h"
#include "Object.h"

void TestScript::Start() {
	tr = gameObject->GetComponent<Transform>();
	inputManager = &gameObject->ctx.inputManager;

	light = lightObj->GetComponent<Light>();
}

void TestScript::Update(float deltaTime) {
	if (inputManager->GetKeyDown(GLFW_KEY_C)) {
		currentColorIndex = (currentColorIndex + 1) % 3;
		light->lightColor = lightColor[currentColorIndex];
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager->GetKeyDown(GLFW_KEY_R)) {
		tr->Rotate(0.0f, rotateSpeed * deltaTime, 0.0f);
	}
	else if (inputManager->GetKeyDown(GLFW_KEY_R)) {
		tr->Rotate(0.0f, -rotateSpeed * deltaTime, 0.0f);
	}
}

Component* TestScript::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TestScript* testScript = obj->AddComponent<TestScript>();
	
	if (props.contains("lightObj")) testScript->lightObj = spawnedObjects.at(props["lightObj"]);

	return testScript;
}

REGISTER_COMPONENT(TestScript);