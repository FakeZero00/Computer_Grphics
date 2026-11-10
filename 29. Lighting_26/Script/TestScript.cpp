#include "TestScript.h"
#include "Object.h"

void TestScript::Start() {
	light = lightObj->GetComponent<Light>();

	orbitTr = orbitObj->GetComponent<Transform>();
	orbitChildTr = orbitChild->GetComponent<Transform>();

	inputManager = &gameObject->ctx.inputManager;
}

void TestScript::Update(float deltaTime) {
	if (inputManager->GetKeyDown(GLFW_KEY_M)) {
		if (isLightOn) {
			light->intensity = 0.1f;
			isLightOn = false;
		}
		else {
			light->intensity = 1.0f;
			isLightOn = true;
		}
	}
}

Component* TestScript::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TestScript* testScript = obj->AddComponent<TestScript>();
	
	if (props.contains("lightObj")) testScript->lightObj = spawnedObjects.at(props["lightObj"].get<string>());
	if (props.contains("objRoot")) testScript->objRoot = spawnedObjects.at(props["objRoot"].get<string>());
	if (props.contains("orbitObj")) testScript->orbitObj = spawnedObjects.at(props["orbitObj"].get<string>());
	if (props.contains("orbitChild")) testScript->orbitChild = spawnedObjects.at(props["orbitChild"].get<string>());

	return testScript;
}

REGISTER_COMPONENT(TestScript);