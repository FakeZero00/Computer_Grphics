#include "TestScript.h"
#include "Object.h"

void TestScript::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void TestScript::Update(float deltaTime) {
	tr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
}

Component* TestScript::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TestScript* testScript = obj->AddComponent<TestScript>();
	
	return testScript;
}

REGISTER_COMPONENT(TestScript);