#include "TestScript.h"
#include "Object.h"

void TestScript::Start() {
	lightObjTr = lightObj->GetComponent<Transform>();
	light = lightObj->GetComponent<Light>();

	objRootTr = objRoot->GetComponent<Transform>();

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

	if (inputManager->GetKeyPressed(GLFW_KEY_Y)) {
		objRootTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_R)) {
		orbitTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
		lightObjTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
	}

	if (inputManager->GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager->GetKeyPressed(GLFW_KEY_Z)) {
		orbitTr->SetLocalScale(orbitTr->scale.x - 0.5f * deltaTime, 1.0f, orbitTr->scale.z - 0.5f * deltaTime);
	}
	else if (inputManager->GetKeyPressed(GLFW_KEY_Z)) {
		orbitTr->SetLocalScale(orbitTr->scale.x + 0.5f * deltaTime, 1.0f, orbitTr->scale.z + 0.5f * deltaTime);
	}

	if (inputManager->GetKeyDown(GLFW_KEY_N)) {
		objRootTr->children[0]->gameObject->isValid = !objRootTr->children[0]->gameObject->isValid;
		objRootTr->children[1]->gameObject->isValid = !objRootTr->children[1]->gameObject->isValid;
	}

	lightObjTr->SetLocalPosition(orbitChildTr->worldPosition);
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