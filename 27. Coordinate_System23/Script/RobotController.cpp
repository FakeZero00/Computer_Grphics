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

	vec3 startRotL = vec3(-rotateAngle, 0.0f, 0.0f);
	quat qStartRotL = quat{ radians(startRotL) };
	vec3 lastRotL = vec3(rotateAngle, 0.0f, 0.0f);
	quat qLastRotL = quat{ radians(lastRotL) };

	vec3 startRotR = -startRotL;
	quat qStartRotR = quat{ radians(startRotR) };
	vec3 lastRotR = -lastRotL;
	quat qLastRotR = quat{ radians(lastRotR) };

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
	else if (inputManager.GetKeyDown(GLFW_KEY_J)) {
		if (isGrounded) {
			rb->AddForce(vec3(0.0f, 20.0f, 0.0f), ForceMode::Impulse);
			isGrounded = false;
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_KP_ADD)) {
		moveSpeed += 2.0f;
		if (moveSpeed >= 22.0f) moveSpeed = 22.0f;
		rotateAngle += 10.0f;
		if (rotateAngle >= 90.0f) rotateAngle = 90.0f;
		rotateSpeed += 0.5f;
		if (rotateSpeed >= 4.5f) rotateSpeed = 4.5f;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_KP_SUBTRACT)) {
		moveSpeed -= 2.0f;
		if (moveSpeed < 10.0f) moveSpeed = 10.0f;
		rotateAngle -= 10.0f;
		if (rotateAngle < 30.0f) rotateAngle = 30.0f;
		rotateSpeed -= 0.5f;
		if (rotateSpeed < 1.5f) rotateSpeed = 1.5f;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_I)) Reset();

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

void RobotController::OnTriggerEnter(Object* other) {
	if (other->name == "Floor") {
		isGrounded = true;
	}
	else if(other->name == "Wall.L" ||
		other->name == "Wall.R" ||
		other->name == "Wall.F" ||
		other->name == "Wall.B") {
		tr->Rotate(0.0f, 180.0f, 0.0f);
		switch (moveMode) {
			case 1:
				moveMode = 2;
				break;
			case 2:
				moveMode = 1;
				break;
			case 3:
				moveMode = 4;
				break;
			case 4:
				moveMode = 3;
				break;
			default:
				break;
		}
	}
}

void RobotController::Reset() {
	moveMode = 0;
	movingBackward = false;
	weight = 0.5f;

	moveSpeed = 10.0f;
	rotateAngle = 30.0f;
	rotateSpeed = 1.5f;
	isGrounded = true;

	tr->SetLocalPosition(vec3{ 0.0f });
	tr->SetLocalRotation(vec3{ 0.0f });
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