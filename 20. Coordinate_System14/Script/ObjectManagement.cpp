#include "ObjectManagement.h"
#include "Object.h"
#include "MeshRenderer3D.h"
#include "InputManager.h"
#include "Transform.h"

void ObjectManagement::Start() {
	cube->isValid = false;
	pyramid->isValid = false;
}

void ObjectManagement::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	Transform* tr;
	MeshRenderer3D* mr;

	if (inputManager.GetKeyDown(GLFW_KEY_C)) {
		cube->isValid = !cube->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_P)) {
		pyramid->isValid = !pyramid->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_H)) {
		if (isDepthTest) {
			glDisable(GL_DEPTH_TEST);
			isDepthTest = false;
		}
		else {
			glEnable(GL_DEPTH_TEST);
			isDepthTest = true;
		}
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyDown(GLFW_KEY_W)) {

		mr = cube->GetComponent<MeshRenderer3D>();
		mr->isValid = true;
		mr->isWireframe = false;

		mr = pyramid->GetComponent<MeshRenderer3D>();
		mr->isValid = true;
		mr->isWireframe = false;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_W)) {
		mr = cube->GetComponent<MeshRenderer3D>();
		mr->isValid = false;
		mr->isWireframe = true;

		mr = pyramid->GetComponent<MeshRenderer3D>();
		mr->isValid = false;
		mr->isWireframe = true;
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
			inputManager.GetKeyDown(GLFW_KEY_X)) {
		if (isXRotation == 2) isXRotation = 0;
		else isXRotation = 2;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_X)) {
		if (isXRotation == 1) isXRotation = 0;
		else isXRotation = 1;
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyDown(GLFW_KEY_Y)) {
		if (isYRotation == 2) isYRotation = 0;
		else isYRotation = 2;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_Y)) {
		if (isYRotation == 1) isYRotation = 0;
		else isYRotation = 1;
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_UP)) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->Translate(0.0f, moveSpeed * deltaTime, 0.0f, true);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->Translate(0.0f, moveSpeed * deltaTime, 0.0f, true);
		}
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_DOWN)) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->Translate(0.0f, -moveSpeed * deltaTime, 0.0f, true);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->Translate(0.0f, -moveSpeed * deltaTime, 0.0f, true);
		}
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT)) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->Translate(moveSpeed * deltaTime, 0.0f, 0.0f, true);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->Translate(moveSpeed * deltaTime, 0.0f, 0.0f, true);
		}
	}
	else if (inputManager.GetKeyPressed(GLFW_KEY_RIGHT)) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->Translate(-moveSpeed * deltaTime, 0.0f, 0.0f, true);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->Translate(-moveSpeed * deltaTime, 0.0f, 0.0f, true);
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_S)) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->SetLocalPosition(0.0f, 0.0f, 0.0f);
			tr->SetLocalRotation(0.0f, 0.0f, 0.0f);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->SetLocalPosition(0.0f, 0.0f, 0.0f);
			tr->SetLocalRotation(0.0f, 0.0f, 0.0f);
		}
	}

	if (isXRotation == 1) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->Rotate(speed * deltaTime, 0.0f, 0.0f, true);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->Rotate(speed * deltaTime, 0.0f, 0.0f, true);
		}
	}
	else if (isXRotation == 2) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->Rotate(-speed * deltaTime, 0.0f, 0.0f, true);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->Rotate(-speed * deltaTime, 0.0f, 0.0f, true);
		}
	}

	if (isYRotation == 1) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->Rotate(0.0f, speed * deltaTime, 0.0f, true);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->Rotate(0.0f, speed * deltaTime, 0.0f, true);
		}
	}
	else if (isYRotation == 2) {
		if (cube->isValid) {
			tr = cube->GetComponent<Transform>();
			tr->Rotate(0.0f, -speed * deltaTime, 0.0f, true);
		}
		if (pyramid->isValid) {
			tr = pyramid->GetComponent<Transform>();
			tr->Rotate(0.0f, -speed * deltaTime, 0.0f, true);
		}
	}
}