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
}