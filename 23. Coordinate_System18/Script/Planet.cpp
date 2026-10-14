#include <Planet.h>
#include "Object.h"
#include "InputManager.h"

void Planet::Start() {
	tr = gameObject->GetComponent<Transform>();
	mr = gameObject->GetComponent<MeshRenderer3D>();
}

void Planet::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyDown(GLFW_KEY_M)) {
		mr->isValid = false;
		mr->isWireframe = true;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_M)) {
		mr->isValid = true;
		mr->isWireframe = false;
	}

	if (isCenter) {
		float speed = 5.0f;
		cout << "Planet: " << gameObject->name << ", Position: (" << tr->position.x << ", " << tr->position.y << ", " << tr->position.z << ")" << endl;

		if (inputManager.GetKeyPressed(GLFW_KEY_W)) {
			tr->Translate(0.0f, speed * deltaTime, 0.0f);
		}
		else if (inputManager.GetKeyPressed(GLFW_KEY_S)) {
			tr->Translate(0.0f, -speed * deltaTime, 0.0f);
		}
		else if (inputManager.GetKeyPressed(GLFW_KEY_A)) {
			tr->Translate(speed * deltaTime, 0.0f, 0.0f);
		}
		else if (inputManager.GetKeyPressed(GLFW_KEY_D)) {
			tr->Translate(-speed * deltaTime, 0.0f, 0.0f);
		}
		else if (inputManager.GetKeyPressed(GLFW_KEY_KP_ADD)) {
			tr->Translate(0.0f, 0.0f, speed * deltaTime);
		}
		else if (inputManager.GetKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
			tr->Translate(0.0f, 0.0f, -speed * deltaTime);
		}
	}
}