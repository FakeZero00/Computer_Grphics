#include "ShapeMovement.h"
#include "InputManager.h"
#include "Object.h"
#include "Material.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Spline.h"
#include "MeshRenderer3D.h"
#include <iostream>
using namespace std;

void ShapeMovement::OnTriggerEnter(Object* other) {
	cout << "Collision Detected with: " << other->name << endl;
	Transform* tr = gameObject->GetComponent<Transform>();

	if(other->name == "Rect_L" || other->name == "Rect_R" ||
		other->name == "Rect_T" || other->name == "Rect_B") {
		if (Movemode == 1) {
			if (other->name == "Rect_L" || other->name == "Rect_R") {
				direction = vec3(-direction.x, direction.y, 0.0f);
			}
			if (other->name == "Rect_T" || other->name == "Rect_B") {
				direction = vec3(direction.x, -direction.y, 0.0f);
			}
		}

		else if (Movemode == 2) {
			Transform* tr = gameObject->GetComponent<Transform>();

			if (other->name == "Rect_L" || other->name == "Rect_R") {
				zigTimer = 0.3f;
				if (isUp && isLeft) {
					tr->Rotate(0.0f, 0.0f, -90.0f);
				}
				else if (isUp && !isLeft) {
					tr->Rotate(0.0f, 0.0f, 90.0f);
				}
				else if (!isUp && isLeft) {
					tr->Rotate(0.0f, 0.0f, 90.0f);
				}
				else if (!isUp && !isLeft) {
					tr->Rotate(0.0f, 0.0f, -90.0f);
				}
				isCollided = true;
			}
			if (other->name == "Rect_T" || other->name == "Rect_B") {
				tr->Rotate(0.0f, 0.0f, 180.0f);
			}
		}

		else if (Movemode == 3) {
			if (other->name == "Rect_L" || other->name == "Rect_R") {
				direction = vec3(-direction.x, direction.y, 0.0f);
			}
			else if (other->name == "Rect_T" || other->name == "Rect_B") {
				direction = vec3(-direction.x, direction.y, 0.0f);
				tr->Rotate(0.0f, 0.0f, 180.0f);
			}
		}
	}
}

void ShapeMovement::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	Transform* tr = gameObject->GetComponent<Transform>();

	if (inputManager.GetKeyDown(GLFW_KEY_1)) {
		if (Movemode == 1) Movemode = 0;
		else Movemode = 1;

		tr->SetLocalRotation(0.0f, 0.0f, 0.0f);

		direction = vec3(urdDir(dre), urdDir(dre), 0.0f);
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_2)) {
		if (Movemode == 2) Movemode = 0;
		else Movemode = 2;

		isUp = true;
		direction = vec3(0.0f, urdDir2(dre), 0.0f);

		float rand = urdDir2(dre);
		if (rand >= 0.5f) {
			tr->SetLocalRotation(0.0f, 0.0f, 90.0f);
			isLeft = true;
		}
		else {
			tr->SetLocalRotation(0.0f, 0.0f, -90.0f);
			isLeft = false;
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_3)) {
		if (Movemode == 3) Movemode = 0;
		else Movemode = 3;

		tr->SetLocalRotation(0.0f, 0.0f, 0.0f);

		direction = vec3(urdDir3(dre), 1.0f, 0.0f);

		float rand = urdDir2(dre);
		if (rand >= 0.5f) tr->Rotate(0.0f, 0.0f, 180.0f);
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_4)) {
		if (Movemode == 4) Movemode = 0;
		else Movemode = 4;

		tr->SetLocalRotation(0.0f, 0.0f, 0.0f);

		direction = vec3(0.0f, 0.01f, 0.0f);

		splineObj = tr->parent->gameObject->Instantiate("Spline");
		vector<vec3> controlPoints = { tr->worldPosition, tr->worldPosition };
		Spline* spline = splineObj->AddComponent<Spline>(controlPoints, gameObject->GetComponent<MeshRenderer3D>()->materials[0]->GetVec4("tColor"));
	}

	if (Movemode != 4 && splineObj != nullptr) {
		splineObj->Destroy();
		splineObj = nullptr;
	}

	if (Movemode == 0) return;
	else if (Movemode == 4) {
		tr->Rotate(0.0f, 0.0f, 45.0f * deltaTime);
		direction.y += 0.02f * deltaTime;

		Spline* spline = splineObj->GetComponent<Spline>();
		spline->controlPoints.push_back(tr->worldPosition);
	}

	if (isCollided && zigTimer > 0.0f) {
		zigTimer -= deltaTime;
	}
	else if (isCollided && zigTimer <= 0.0f) {
		isCollided = false;
		Timerbool = true;
	}
	if (Timerbool) {
		if (isUp && isLeft) {
			tr->Rotate(0.0f, 0.0f, -90.0f);
		}
		else if (isUp && !isLeft) {
			tr->Rotate(0.0f, 0.0f, 90.0f);
		}
		else if (!isUp && isLeft) {
			tr->Rotate(0.0f, 0.0f, 90.0f);
		}
		else if (!isUp && !isLeft) {
			tr->Rotate(0.0f, 0.0f, -90.0f);
		}
		isLeft = !isLeft;
		Timerbool = false;
	}

	tr->Translate(direction.x * deltaTime, direction.y * deltaTime, 0.0f);
}