#include "TruckController.h"

void TruckController::Start() {
	tr = gameObject->GetComponent<Transform>();
	railGeneratorTr = railGenerator->GetComponent<Transform>();
}

void TruckController::Update(float deltaTime) {
	if(Cube1 == nullptr && railGeneratorTr != nullptr && railGeneratorTr->children.size() >= 6) {
		Cube1 = railGeneratorTr->children[20]->gameObject;
		Cube2 = railGeneratorTr->children[21]->gameObject;
		Cube3 = railGeneratorTr->children[22]->gameObject;
		Cube4 = railGeneratorTr->children[23]->gameObject;
		Cube5 = railGeneratorTr->children[24]->gameObject;

		cube1Movement = Cube1->GetComponent<CubeMovement>();
		cube2Movement = Cube2->GetComponent<CubeMovement>();
		cube3Movement = Cube3->GetComponent<CubeMovement>();
		cube4Movement = Cube4->GetComponent<CubeMovement>();
		cube5Movement = Cube5->GetComponent<CubeMovement>();
	}
	
	InputManager inputManager = gameObject->ctx.inputManager;

	if (cube1Movement != nullptr) {
		if (inputManager.GetKeyDown(GLFW_KEY_1)) {
			cube1Movement->Load2Truck(truckCube1);
		}
	}
	if (cube2Movement != nullptr) {
		if (inputManager.GetKeyDown(GLFW_KEY_2)) {
			cube2Movement->Load2Truck(truckCube2);
		}
	}
	if (cube3Movement != nullptr) {
		if (inputManager.GetKeyDown(GLFW_KEY_3)) {
			cube3Movement->Load2Truck(truckCube3);
		}
	}
	if (cube4Movement != nullptr) {
		if (inputManager.GetKeyDown(GLFW_KEY_4)) {
			cube4Movement->Load2Truck(truckCube4);
		}
	}
	if (cube5Movement != nullptr) {
		if (inputManager.GetKeyDown(GLFW_KEY_5)) {
			cube5Movement->Load2Truck(truckCube5);
		}
	}

	if (inputManager.GetKeyDown(GLFW_KEY_G)) {
		isMove = !isMove;
	}

	if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		isMove = false;
		moveWeight = 0.0f;
	}

	if (isMove) {
		moveWeight += moveSpeed * deltaTime;
		if (moveWeight >= 1.0f) moveWeight = 1.0f;
	}
	else {
		moveWeight -= moveSpeed * deltaTime;
		if (moveWeight < 0.0f) moveWeight = 0.0f;
	}

	vec3 currentPos = glm::mix(startPos, endPos, moveWeight);
	tr->SetLocalPosition(currentPos);
}

Component* TruckController::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TruckController* truckController = obj->AddComponent<TruckController>();

	if (props.contains("railGenerator")) truckController->railGenerator = spawnedObjects.at(props["railGenerator"]);
	if (props.contains("truckCube1")) truckController->truckCube1 = spawnedObjects.at(props["truckCube1"])->GetComponent<Transform>();
	if (props.contains("truckCube2")) truckController->truckCube2 = spawnedObjects.at(props["truckCube2"])->GetComponent<Transform>();
	if (props.contains("truckCube3")) truckController->truckCube3 = spawnedObjects.at(props["truckCube3"])->GetComponent<Transform>();
	if (props.contains("truckCube4")) truckController->truckCube4 = spawnedObjects.at(props["truckCube4"])->GetComponent<Transform>();
	if (props.contains("truckCube5")) truckController->truckCube5 = spawnedObjects.at(props["truckCube5"])->GetComponent<Transform>();

	return truckController;
}

REGISTER_COMPONENT(TruckController);