#include "CameraControl.h"

void CameraControl::Start() {
	tr = gameObject->GetComponent<Transform>();

	railGeneratorTr = railGenerator->GetComponent<Transform>();

	cam = gameObject->GetComponent<Camera>();
}

void CameraControl::Update(float deltaTime) {
	if (Cube1 == nullptr && railGeneratorTr != nullptr && railGeneratorTr->children.size() >= 6) {
		Cube1 = railGeneratorTr->children[20]->gameObject;
		Cube2 = railGeneratorTr->children[21]->gameObject;
		Cube3 = railGeneratorTr->children[22]->gameObject;
		Cube4 = railGeneratorTr->children[23]->gameObject;
		Cube5 = railGeneratorTr->children[24]->gameObject;

		Cube1Tr = Cube1->GetComponent<Transform>();
		Cube2Tr = Cube2->GetComponent<Transform>();
		Cube3Tr = Cube3->GetComponent<Transform>();
		Cube4Tr = Cube4->GetComponent<Transform>();
		Cube5Tr = Cube5->GetComponent<Transform>();
	}

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

	if (inputManager.GetKeyDown(GLFW_KEY_V)) {
		if (!isFPS) {
			isFPS = true;
			cubeNum = 5;
			tr->SetLocalRotation(Cube5Tr->rotation);
			tr->SetLocalPosition(Cube5Tr->worldPosition);
			tr->Translate(vec3{ -0.5f, 0.75, -0.55 });
		}
		else {
			isFPS = false;
			cubeNum = 0;
			tr->SetLocalPosition(0.0f, 5.0f, 5.0f);
			tr->SetLocalRotation(45.0f, 180.0f, 0.0f);
		}
	}

	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyDown(GLFW_KEY_N)) {
		cubeNum -= 1;
		if (cubeNum < 0) cubeNum = 5;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_N)) {
		cubeNum = (cubeNum + 1) % 6;
		if (cubeNum == 0) cubeNum = 1;
	}

	if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		cam->fov = 60.0f;
		cam->isOrthographic = false;
		camArmTr->SetLocalRotation(0.0f, 0.0f, 0.0f);
		cubeNum = 0;
		gameObject->GetComponent<Transform>()->SetLocalPosition(0.0f, 5.0f, 5.0f);
		gameObject->GetComponent<Transform>()->SetLocalRotation(45.0f, 180.0f, 0.0f);
	}

	if (cubeNum != 0 && isFPS) {
		switch (cubeNum) {
		case 1:
			tr->SetLocalRotation(Cube1Tr->rotation);
			tr->SetLocalPosition(Cube1Tr->worldPosition);
			tr->Translate(vec3{ -0.5f, 0.75, -0.55 });
			break;
		case 2:
			tr->SetLocalRotation(Cube2Tr->rotation);
			tr->SetLocalPosition(Cube2Tr->worldPosition);
			tr->Translate(vec3{ -0.5f, 0.75, -0.55 });
			break;
		case 3:
			tr->SetLocalRotation(Cube3Tr->rotation);
			tr->SetLocalPosition(Cube3Tr->worldPosition);
			tr->Translate(vec3{ -0.5f, 0.75, -0.55 });
			break;
		case 4:
			tr->SetLocalRotation(Cube4Tr->rotation);
			tr->SetLocalPosition(Cube4Tr->worldPosition);
			tr->Translate(vec3{ -0.5f, 0.75, -0.55 });
			break;
		case 5:
			tr->SetLocalRotation(Cube5Tr->rotation);
			tr->SetLocalPosition(Cube5Tr->worldPosition);
			tr->Translate(vec3{ -0.5f, 0.75, -0.55 });
			break;
		}
	}
}

Component* CameraControl::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	CameraControl* cameraControl = obj->AddComponent<CameraControl>();

	cameraControl->camArmTr = spawnedObjects.at(props["camArmTr"])->GetComponent<Transform>();
	if (props.contains("railGenerator")) cameraControl->railGenerator = spawnedObjects.at(props["railGenerator"]);

	return cameraControl;
}

REGISTER_COMPONENT(CameraControl);