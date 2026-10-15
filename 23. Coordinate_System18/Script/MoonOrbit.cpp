#include <MoonOrbit.h>
#include "Object.h"

void MoonOrbit::Start() {
	tr = gameObject->GetComponent<Transform>();
	parentTr = parentPlanet->GetComponent<Transform>();
}

void MoonOrbit::Update(float deltaTime) {
	float rotationSpeed = 20.0f; //회전 속도
	tr->SetLocalPosition(parentTr->worldPosition.x, parentTr->worldPosition.y, parentTr->worldPosition.z);
	tr->Rotate(0.0f, rotationSpeed * deltaTime, 0.0f);

	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_1)) {
		isScaling = !isScaling;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_3)) {
		isRotating = !isRotating;
	}

	if (isScaling) {
		scaleWeight += deltaTime;
		if (scaleWeight >= 1.0f) scaleWeight = 1.0f;
	}
	else {
		scaleWeight -= deltaTime;
		if (scaleWeight <= 0.0f) scaleWeight = 0.0f;
	}

	vec3 startScale = { 1.0f, 1.0f, 1.0f };
	vec3 endScale = { 2.0f, 2.0f, 2.0f };
	vec3 newScale = mix(startScale, endScale, scaleWeight);

	tr->SetLocalScale(newScale.x, newScale.y, newScale.z);

	if (isRotating) {
		float rotationSpeed = 50.0f; //회전 속도
		tr->Rotate(0.0f, 0.0f, rotationSpeed * deltaTime);
	}
}