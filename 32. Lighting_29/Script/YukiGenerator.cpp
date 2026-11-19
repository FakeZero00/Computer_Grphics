#include "YukiGenerator.h"
#include "SphereCollider.h"
#include "Transform.h"
#include <iostream>
using namespace std;

void YukiGenerator::Start() {
	inputManager = &gameObject->ctx.inputManager;

	//Yuki 생성
	for (int i = 0; i < 200; i++) {
		Object* yuki = gameObject->Instantiate("Yuki" + to_string(i));
		Transform* tr = yuki->GetComponent<Transform>();
		tr->SetLocalPosition(distX(dre), distY(dre), distZ(dre));
		tr->SetLocalScale(0.1f, 0.1f, 0.1f);
		yuki->AddComponent<MeshRenderer3D>(yukiMesh, yukiMaterial);
		yuki->AddComponent<SphereCollider>();
		yuki->AddComponent<RigidBody>()->useGravity = false;
		yukiObjects.push_back(yuki);
		yukiSpeeds.push_back(distSpeed(dre));
		yukiTransforms.push_back(tr);
		yuki->isValid = false;
	}
}

void YukiGenerator::Update(float deltaTime) {
	if (inputManager->GetKeyDown(GLFW_KEY_S)) {
		if (!isSnow) {
			isSnow = true;
			for (int i = 0; i < yukiObjects.size(); i++) {
				Object* yuki = yukiObjects[i];
				yuki->isValid = true;
			}
		}
		else {
			isSnow = false;
			for (int i = 0; i < yukiObjects.size(); i++) {
				Object* yuki = yukiObjects[i];
				Transform* tr = yukiTransforms[i];
				tr->SetLocalPosition(distX(dre), distY(dre), distZ(dre));
				yukiSpeeds[i] = distSpeed(dre);
				yuki->isValid = false;
			}
		}
	}
	
	if (isSnow) {
		for (int i = 0; i < yukiObjects.size(); i++) {
			Object* yuki = yukiObjects[i];
			Transform* tr = yukiTransforms[i];
			tr->Translate(0.0f, -yukiSpeeds[i] * deltaTime, 0.0f);
			if (tr->worldPosition.y < -1.0f) {
				tr->SetLocalPosition(distX(dre), distY(dre), distZ(dre));
				yukiSpeeds[i] = distSpeed(dre);
			}
		}
	}
}

Component* YukiGenerator::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	YukiGenerator* script = obj->AddComponent<YukiGenerator>();
	
	return script;
}

REGISTER_COMPONENT(YukiGenerator);