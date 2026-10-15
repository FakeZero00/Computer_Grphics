#include <Orbit.h>
#include "Object.h"
#include <gl/glm/glm.hpp>
using namespace glm;

void Orbit::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void Orbit::Update(float deltaTime) {
	float rotationSpeed = 20.0f; //회전 속도
	tr->Rotate(0.0f, rotationSpeed * deltaTime, 0.0f);

	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_1)) {
		isScaling = !isScaling;
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
}