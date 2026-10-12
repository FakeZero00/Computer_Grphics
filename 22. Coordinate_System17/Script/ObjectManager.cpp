#include "ObjectManager.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "InputManager.h"
#include "Material.h"
#include <map>

extern map<string, GLuint> shaders;

void ObjectManager::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		if (childL == nullptr) {
			Material* localPosColorMat = new Material(shaders["LocalPosColor"]);

			childL = gameObject->Instantiate("Child_L_Parent");
			childL = childL->Instantiate("Child_L");
			childL->AddComponent<MeshRenderer3D>(meshes[uid(dre)], localPosColorMat);

			if (childRPos == vec3(0.0f, 0.0f, 0.0f)) {
				childLPos = vec3(ufdL(dre), 0.0f, 0.0f);
			}
			else {
				childLPos = -childRPos;
			}
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->SetLocalPosition(childLPos.x, childLPos.y, childLPos.z);
			childLTr->SetLocalRotation(30.0f, 30.0f, 0.0f);
		}
	}
	else if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (childR == nullptr) {
			Material* localPosColorMat = new Material(shaders["LocalPosColor"]);

			childR = gameObject->Instantiate("Child_R_Parent");
			childR = childR->Instantiate("Child_R");
			childR->AddComponent<MeshRenderer3D>(meshes[uid(dre)], localPosColorMat);

			if (childLPos == vec3(0.0f, 0.0f, 0.0f)) {
				childRPos = vec3(ufdR(dre), 0.0f, 0.0f);
			}
			else {
				childRPos = -childLPos;
			}
			Transform* childRTr = childR->GetComponent<Transform>();
			childRTr->SetLocalPosition(childRPos.x, childRPos.y, childRPos.z);
			childRTr->SetLocalRotation(30.0f, 30.0f, 0.0f);
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_1)) commandMode = 1;
	else if (inputManager.GetKeyDown(GLFW_KEY_2)) commandMode = 2;
	else if (inputManager.GetKeyDown(GLFW_KEY_3)) commandMode = 3;

	if (childL != nullptr) {
		if (inputManager.GetKeyDown(GLFW_KEY_C)) {
			MeshRenderer3D* mr = childL->GetComponent<MeshRenderer3D>();
			mr->mesh = meshes[uid(dre)];
		}

		if (commandMode == 1 || commandMode == 3) {
			if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_X)) {
				if (isXRotatingL == 2) isXRotatingL = 0;
				else isXRotatingL = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_X)) {
				if (isXRotatingL == 1) isXRotatingL = 0;
				else isXRotatingL = 1;
			}
		}

		if (isXRotatingL == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Rotate(90.0f * deltaTime, 0.0f, 0.0f, true);
		}
		else if (isXRotatingL == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Rotate(-90.0f * deltaTime, 0.0f, 0.0f, true);
		}
	}

	if (childR != nullptr) {
		if (inputManager.GetKeyDown(GLFW_KEY_C)) {
			MeshRenderer3D* mr = childR->GetComponent<MeshRenderer3D>();
			mr->mesh = meshes[uid(dre)];
		}

		if (commandMode == 2 || commandMode == 3) {

		}
	}
}