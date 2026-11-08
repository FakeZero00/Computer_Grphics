#include "Door.h"
#include "Object.h"

void Door::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void Door::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_O)) {
		opening = !opening;
	}
	if (inputManager.GetKeyDown(GLFW_KEY_I)) Reset();

	if (opening) {
		weight += deltaTime;
		if (weight >= 1.0f) weight = 1.0f;
	}
	else {
		weight -= deltaTime;
		if (weight <= 0.0f) weight = 0.0f;
	}

	vec3 currentPos = glm::mix(startPos, endPos, weight);
	tr->SetLocalPosition(currentPos);
}

void Door::Reset() {
	weight = 0.0f;
	opening = false;
	tr->SetLocalPosition(startPos);
}

Component* Door::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	Door* door = obj->AddComponent<Door>();

	return door;
}

REGISTER_COMPONENT(Door);