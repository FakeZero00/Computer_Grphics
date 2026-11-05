#include "RobotController.h"
#include "Object.h"

void RobotController::Start() {
	tr = gameObject->GetComponent<Transform>();
	rb = gameObject->GetComponent<RigidBody>();
}

void RobotController::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyPressed(GLFW_KEY_R)) {
		rb->AddForce(vec3(0.0f, 0.0f, -10.0f), ForceMode::Impulse);
	}
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