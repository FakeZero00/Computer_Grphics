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
			else if(inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_Y)) {
				if (isYRotatingL == 2) isYRotatingL = 0;
				else isYRotatingL = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_Y)) {
				if (isYRotatingL == 1) isYRotatingL = 0;
				else isYRotatingL = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_R)) {
				if (isRRotatingL == 2) isRRotatingL = 0;
				else isRRotatingL = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_R)) {
				if (isRRotatingL == 1) isRRotatingL = 0;
				else isRRotatingL = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_A)) {
				if (isAScalingL == 2) isAScalingL = 0;
				else isAScalingL = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_A)) {
				if (isAScalingL == 1) isAScalingL = 0;
				else isAScalingL = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_B)) {
				if (isBScalingL == 2) isBScalingL = 0;
				else isBScalingL = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_B)) {
				if (isBScalingL == 1) isBScalingL = 0;
				else isBScalingL = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_D)) {
				if (isDMovingL == 2) isDMovingL = 0;
				else isDMovingL = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_D)) {
				if (isDMovingL == 1) isDMovingL = 0;
				else isDMovingL = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_E)) {
				if (isEMovingL == 2) isEMovingL = 0;
				else isEMovingL = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_E)) {
				if (isEMovingL == 1) isEMovingL = 0;
				else isEMovingL = 1;
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

		if (isYRotatingL == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
		}
		else if (isYRotatingL == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Rotate(0.0f, -90.0f * deltaTime, 0.0f, true);
		}

		if (isRRotatingL == 1) {
			Transform* childLTr = childL->GetComponent<Transform>()->parent;
			childLTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
		}
		else if (isRRotatingL == 2) {
			Transform* childLTr = childL->GetComponent<Transform>()->parent;
			childLTr->Rotate(0.0f, -90.0f * deltaTime, 0.0f, true);
		}

		if (isAScalingL == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->SetLocalScale(childLTr->scale.x + deltaTime, childLTr->scale.y + deltaTime, childLTr->scale.z + deltaTime);
		}
		else if (isAScalingL == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->SetLocalScale(childLTr->scale.x - deltaTime, childLTr->scale.y - deltaTime, childLTr->scale.z - deltaTime);
		}

		if (isBScalingL == 1) {
			Transform* childLTr = childL->GetComponent<Transform>()->parent;
			childLTr->SetLocalScale(childLTr->scale.x + deltaTime, childLTr->scale.y + deltaTime, childLTr->scale.z + deltaTime);
		}
		else if (isBScalingL == 2) {
			Transform* childLTr = childL->GetComponent<Transform>()->parent;
			childLTr->SetLocalScale(childLTr->scale.x - deltaTime, childLTr->scale.y - deltaTime, childLTr->scale.z - deltaTime);
		}

		if (isDMovingL == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Translate(5.0f * deltaTime, 0.0f, 0.0f, true);
		}
		else if (isDMovingL == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Translate(-5.0f * deltaTime, 0.0f, 0.0f, true);
		}

		if (isEMovingL == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Translate(0.0f, 5.0f * deltaTime, 0.0f, true);
		}
		else if (isEMovingL == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Translate(0.0f, -5.0f * deltaTime, 0.0f, true);
		}
	}

	if (childR != nullptr) {
		if (inputManager.GetKeyDown(GLFW_KEY_C)) {
			MeshRenderer3D* mr = childR->GetComponent<MeshRenderer3D>();
			mr->mesh = meshes[uid(dre)];
		}

		if (commandMode == 2 || commandMode == 3) {
			if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_X)) {
				if (isXRotatingR == 2) isXRotatingR = 0;
				else isXRotatingR = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_X)) {
				if (isXRotatingR == 1) isXRotatingR = 0;
				else isXRotatingR = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_Y)) {
				if (isYRotatingR == 2) isYRotatingR = 0;
				else isYRotatingR = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_Y)) {
				if (isYRotatingR == 1) isYRotatingR = 0;
				else isYRotatingR = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_R)) {
				if (isRRotatingR == 2) isRRotatingR = 0;
				else isRRotatingR = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_R)) {
				if (isRRotatingR == 1) isRRotatingR = 0;
				else isRRotatingR = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_A)) {
				if (isAScalingR == 2) isAScalingR = 0;
				else isAScalingR = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_A)) {
				if (isAScalingR == 1) isAScalingR = 0;
				else isAScalingR = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_B)) {
				if (isBScalingR == 2) isBScalingR = 0;
				else isBScalingR = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_B)) {
				if (isBScalingR == 1) isBScalingR = 0;
				else isBScalingR = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_D)) {
				if (isDMovingR == 2) isDMovingR = 0;
				else isDMovingR = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_D)) {
				if (isDMovingR == 1) isDMovingR = 0;
				else isDMovingR = 1;
			}
			else if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
				inputManager.GetKeyDown(GLFW_KEY_E)) {
				if (isEMovingR == 2) isEMovingR = 0;
				else isEMovingR = 2;
			}
			else if (inputManager.GetKeyDown(GLFW_KEY_E)) {
				if (isEMovingR == 1) isEMovingR = 0;
				else isEMovingR = 1;
			}
		}

		if (isXRotatingR == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Rotate(90.0f * deltaTime, 0.0f, 0.0f, true);
		}
		else if (isXRotatingR == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Rotate(-90.0f * deltaTime, 0.0f, 0.0f, true);
		}

		if (isYRotatingR == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
		}
		else if (isYRotatingR == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Rotate(0.0f, -90.0f * deltaTime, 0.0f, true);
		}

		if (isRRotatingR == 1) {
			Transform* childLTr = childL->GetComponent<Transform>()->parent;
			childLTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
		}
		else if (isRRotatingR == 2) {
			Transform* childLTr = childL->GetComponent<Transform>()->parent;
			childLTr->Rotate(0.0f, -90.0f * deltaTime, 0.0f, true);
		}

		if (isAScalingR == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->SetLocalScale(childLTr->scale.x + deltaTime, childLTr->scale.y + deltaTime, childLTr->scale.z + deltaTime);
		}
		else if (isAScalingR == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->SetLocalScale(childLTr->scale.x - deltaTime, childLTr->scale.y - deltaTime, childLTr->scale.z - deltaTime);
		}

		if (isBScalingR == 1) {
			Transform* childLTr = childL->GetComponent<Transform>()->parent;
			childLTr->SetLocalScale(childLTr->scale.x + deltaTime, childLTr->scale.y + deltaTime, childLTr->scale.z + deltaTime);
		}
		else if (isBScalingR == 2) {
			Transform* childLTr = childL->GetComponent<Transform>()->parent;
			childLTr->SetLocalScale(childLTr->scale.x - deltaTime, childLTr->scale.y - deltaTime, childLTr->scale.z - deltaTime);
		}

		if (isDMovingR == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Translate(5.0f * deltaTime, 0.0f, 0.0f, true);
		}
		else if (isDMovingR == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Translate(-5.0f * deltaTime, 0.0f, 0.0f, true);
		}

		if (isEMovingR == 1) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Translate(0.0f, 5.0f * deltaTime, 0.0f, true);
		}
		else if (isEMovingR == 2) {
			Transform* childLTr = childL->GetComponent<Transform>();
			childLTr->Translate(0.0f, -5.0f * deltaTime, 0.0f, true);
		}
	}

	if (childL != nullptr && childR != nullptr) {
		Transform* childLTr = childL->GetComponent<Transform>();
		Transform* childRTr = childR->GetComponent<Transform>();
		
		if (inputManager.GetKeyDown(GLFW_KEY_T)) {
			if (istMovingL == 0 && istMovingR == 0) {
				istMovingL = 1;
				istMovingR = 1;
				tMovingL = 0.0f;
				tMovingR = 0.0f;

				childLPos = childLTr->position;
				childRPos = childRTr->position;

				targetPosL = childRPos;
				targetPosR = childLPos;
			}
		}

		if (istMovingL == 1 || istMovingL == 2) {
			tMovingL += deltaTime;
			if (tMovingL >= 1.0f) {
				tMovingL = 0.0f;
				if (istMovingL == 1) istMovingL = 2;
				else if (istMovingL == 2) istMovingL = 0;
			}

			if (istMovingL == 1) {
				vec3 endPos{ 0.0f, 0.0f, 0.0f };
				vec3 newPos = mix(childLPos, endPos, tMovingL);
				childLTr->SetLocalPosition(newPos.x, newPos.y, newPos.z);
			}
			else if (istMovingL == 2) {
				vec3 startPos{ 0.0f, 0.0f, 0.0f };
				vec3 newPos = mix(startPos, targetPosL, tMovingL);
				childLTr->SetLocalPosition(newPos.x, newPos.y, newPos.z);
			}
		}

		if (istMovingR == 1 || istMovingR == 2) {
			tMovingR += deltaTime;
			if (tMovingR >= 1.0f) {
				tMovingR = 0.0f;
				if (istMovingR == 1) istMovingR = 2;
				else if (istMovingR == 2) istMovingR = 0;
			}

			if (istMovingR == 1) {
				vec3 endPos{ 0.0f, 0.0f, 0.0f };
				vec3 newPos = mix(childRPos, endPos, tMovingR);
				childRTr->SetLocalPosition(newPos.x, newPos.y, newPos.z);
			}
			else if (istMovingR == 2) {
				vec3 startPos{ 0.0f, 0.0f, 0.0f };
				vec3 newPos = mix(startPos, targetPosR, tMovingR);
				childRTr->SetLocalPosition(newPos.x, newPos.y, newPos.z);
			}
		}
	}
}