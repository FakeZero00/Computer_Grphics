#include "RobotController.h"
#include "Object.h"

void RobotController::Start() {
	tr = gameObject->GetComponent<Transform>();
	rb = gameObject->GetComponent<RigidBody>();

	ArmLtr = ArmL->GetComponent<Transform>();
	ArmRtr = ArmR->GetComponent<Transform>();
	LegLtr = LegL->GetComponent<Transform>();
	LegRtr = LegR->GetComponent<Transform>();
}

void RobotController::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_W)) {
		if (moveMode == 1) moveMode = 0;
		else {
			moveMode = 1;
			tr->SetLocalRotation(0.0f, 180.0f, 0.0f);
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_S)) {
		if (moveMode == 2) moveMode = 0;
		else {
			moveMode = 2;
			tr->SetLocalRotation(0.0f, 0.0f, 0.0f);
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_A)) {
		if (moveMode == 3) moveMode = 0;
		else {
			moveMode = 3;
			tr->SetLocalRotation(0.0f, -90.0f, 0.0f);
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_D)) {
		if (moveMode == 4) moveMode = 0;
		else {
			moveMode = 4;
			tr->SetLocalRotation(0.0f, 90.0f, 0.0f);
		}
	}

	if (moveMode != 0) {
		tr->Translate(0.0f, 0.0f, moveSpeed * deltaTime);
	}

	//팔 다리 흔들기
	if (moveMode != 0) {
		if (!movingBackward) {
			weight += 1.5f * deltaTime;
			if (weight >= 1.0f) {
				weight = 1.0f;
				movingBackward = true;
			}
		}
		else {
			weight -= 1.5f * deltaTime;
			if (weight <= 0.0f) {
				weight = 0.0f;
				movingBackward = false;
			}
		}
	}

	quat currentRotL = glm::slerp(qStartRotL, qLastRotL, weight);
	quat currentRotR = glm::slerp(qStartRotR, qLastRotR, weight);

	ArmLtr->SetLocalRotation(currentRotL);
	ArmRtr->SetLocalRotation(currentRotR);
	LegLtr->SetLocalRotation(currentRotR);
	LegRtr->SetLocalRotation(currentRotL);
}

void RobotController::OnTriggerStay(Object* other) {
	cout << "Trigger Entered with object: " << other->name << endl;
}

Component* RobotController::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	RobotController* robotController = obj->AddComponent<RobotController>();
	
	if (props.contains("ArmL")) {
		robotController->ArmL = spawnedObjects.at(props["ArmL"]);
	}
	if (props.contains("ArmR")) {
		robotController->ArmR = spawnedObjects.at(props["ArmR"]);
	}
	if (props.contains("LegL")) {
		robotController->LegL = spawnedObjects.at(props["LegL"]);
	}
	if (props.contains("LegR")) {
		robotController->LegR = spawnedObjects.at(props["LegR"]);
	}

	return robotController;
}

REGISTER_COMPONENT(RobotController);