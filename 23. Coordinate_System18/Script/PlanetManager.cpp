#include "PlanetManager.h"
#include "InputManager.h"
#include "Object.h"

void PlanetManager::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyDown(GLFW_KEY_P)) {
		cam->isOrthographic = true;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_P)) {
		cam->isOrthographic = false;
	}

	float speed = 5.0f;
	if (inputManager.GetKeyPressed(GLFW_KEY_W)) {
		centerTr->Translate(0.0f, speed * deltaTime, 0.0f);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_S)) {
		centerTr->Translate(0.0f, -speed * deltaTime, 0.0f);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_A)) {
		centerTr->Translate(speed * deltaTime, 0.0f, 0.0f);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_D)) {
		centerTr->Translate(-speed * deltaTime, 0.0f, 0.0f);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_KP_ADD)) {
		centerTr->Translate(0.0f, 0.0f, speed * deltaTime);
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
		centerTr->Translate(0.0f, 0.0f, -speed * deltaTime);
	}
}