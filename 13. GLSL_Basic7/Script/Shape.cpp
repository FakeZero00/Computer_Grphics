#include "Shape.h"
#include "Material.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "BoxCollider.h"
#include "InputManager.h"

void Shape::Select() {
	isSelected = true;
	MeshRenderer3D* renderer = gameObject->GetComponent<MeshRenderer3D>();
	if(renderer) gameObject->GetComponent<MeshRenderer3D>()->materials[0]->isOutline = true;
	else {
		gameObject->GetComponent<BoxCollider>()->isDebug = true;
	}
}

void Shape::Deselect() {
	isSelected = false;
	MeshRenderer3D* renderer = gameObject->GetComponent<MeshRenderer3D>();
	if (renderer) gameObject->GetComponent<MeshRenderer3D>()->materials[0]->isOutline = false;
	else {
		gameObject->GetComponent<BoxCollider>()->isDebug = false;
	}
}

void Shape::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (isSelected) {
		Transform* tr = gameObject->GetComponent<Transform>();
		if (inputManager.GetKeyPressed(GLFW_KEY_W) || inputManager.GetKeyPressed(GLFW_KEY_3)) tr->Translate(0.0f, moveSpeed * deltaTime, 0.0f, true);
		else if (inputManager.GetKeyPressed(GLFW_KEY_S) || inputManager.GetKeyPressed(GLFW_KEY_4)) tr->Translate(0.0f, -moveSpeed * deltaTime, 0.0f, true);
		else if (inputManager.GetKeyPressed(GLFW_KEY_A) || inputManager.GetKeyPressed(GLFW_KEY_1)) tr->Translate(-moveSpeed * deltaTime, 0.0f, 0.0f, true);
		else if (inputManager.GetKeyPressed(GLFW_KEY_D) || inputManager.GetKeyPressed(GLFW_KEY_2)) tr->Translate(moveSpeed * deltaTime, 0.0f, 0.0f, true);
		else if (inputManager.GetKeyPressed(GLFW_KEY_I)) tr->Translate(-moveSpeed * deltaTime, moveSpeed * deltaTime, 0.0f, true);
		else if (inputManager.GetKeyPressed(GLFW_KEY_K)) tr->Translate(-moveSpeed * deltaTime, -moveSpeed * deltaTime, 0.0f, true);
		else if (inputManager.GetKeyPressed(GLFW_KEY_O)) tr->Translate(moveSpeed * deltaTime, moveSpeed * deltaTime, 0.0f, true);
		else if (inputManager.GetKeyPressed(GLFW_KEY_L)) tr->Translate(moveSpeed * deltaTime, -moveSpeed * deltaTime, 0.0f, true);
	}
}