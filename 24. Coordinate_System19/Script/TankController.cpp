#include "TankController.h"
#include "Object.h"

void TankController::Start() {
	tr = gameObject->GetComponent<Transform>();
	inputManager = gameObject->ctx.inputManager;
}

void TankController::Update(float deltaTime) {

}

Component* TankController::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	TankController* tankController = obj->AddComponent<TankController>();

	tankController->camTr = spawnedObjects.at(props["camTr"])->GetComponent<Transform>();
	tankController->BottomTr_L = spawnedObjects.at(props["BottomTr_L"])->GetComponent<Transform>();
	tankController->BottomTr_R = spawnedObjects.at(props["BottomTr_R"])->GetComponent<Transform>();
	tankController->MiddleTr = spawnedObjects.at(props["MiddleTr"])->GetComponent<Transform>();
	tankController->TopTr_L = spawnedObjects.at(props["TopTr_L"])->GetComponent<Transform>();
	tankController->TopTr_R = spawnedObjects.at(props["TopTr_R"])->GetComponent<Transform>();
	tankController->BarrelTr_L = spawnedObjects.at(props["BarrelTr_L"])->GetComponent<Transform>();
	tankController->BarrelTr_R = spawnedObjects.at(props["BarrelTr_R"])->GetComponent<Transform>();
	tankController->FlagTr_L = spawnedObjects.at(props["FlagTr_L"])->GetComponent<Transform>();
	tankController->FlagTr_R = spawnedObjects.at(props["FlagTr_R"])->GetComponent<Transform>();

	return tankController;
}

REGISTER_COMPONENT(TankController);