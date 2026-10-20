#include "TestScript.h"
#include "Object.h"

void TestScript::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void TestScript::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyPressed(GLFW_KEY_R)) {
		tr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
	}
	if (inputManager.GetKeyPressed(GLFW_KEY_UP)) {
		tr->Translate(0.0f, 2.0f * deltaTime, 0.0f);
	}
}

Component* TestScript::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TestScript* testScript = obj->AddComponent<TestScript>();
	
	return testScript;
}

REGISTER_COMPONENT(TestScript);