#include "DirectorScript.h"
#include "Object.h"
#include "AppContext.h"
#include "Transform.h"
#include "InputManager.h"
#include "MeshRenderer2D.h"
#include "BoxCollider2D.h"
#include "SquareMovement.h"
#include <random>
#include <ranges>

void DirectorScript::Update(float deltaTime) {
	InputManager& inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_A)) {
		if (count < 10) {
			random_device rd;
			default_random_engine dre{ rd() };
			uniform_real_distribution<float> urd{ -0.7f, 0.7f };
			uniform_real_distribution<float> urd2{ 0.0f, 1.0f };
			uniform_real_distribution<float> urd3{ 0.1f, 0.3f };

			Object* nSquare = gameObject->Instantiate(string{"Square ("} + to_string(count) + string{")"});
			Transform* nSquareTr = nSquare->GetComponent<Transform>();
			nSquareTr->SetLocalPosition(urd(dre), urd(dre), 0.0f);
			float size = urd3(dre);
			MeshRenderer2D* nSquareMR = nSquare->AddComponent<MeshRenderer2D>(size, size, Color{urd2(dre), urd2(dre), urd2(dre), 1.0f});
			BoxCollider2D* nSquareBC = nSquare->AddComponent<BoxCollider2D>(size, size);
			nSquare->AddComponent<SquareMovement>();

			count++;
		}
	}

	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		for (auto& col : views::reverse(gameObject->ctx.CollisionObjects)) {
			if (col->Contains(inputManager.GetMouseX(), inputManager.GetMouseY())) {
				Object* targetObj = col->gameObject;
				targetObj->GetComponent<SquareMovement>()->isMoving = true;
				break;
			}
		}
	}

	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_RIGHT)) {
		for (auto& col : views::reverse(gameObject->ctx.CollisionObjects)) {
			if (col->Contains(inputManager.GetMouseX(), inputManager.GetMouseY())) {
				Object* targetObj = col->gameObject;
				targetObj->GetComponent<SquareMovement>()->Seperate();
				break;
			}
		}
	}

	if (inputManager.GetKeyUp(GLFW_MOUSE_BUTTON_LEFT)) {
		for (auto& col : views::reverse(gameObject->ctx.CollisionObjects)) {
			if (col->gameObject->GetComponent<SquareMovement>()->isMoving) {
				col->gameObject->GetComponent<SquareMovement>()->isMoving = false;

				if (col->gameObject->GetComponent<BoxCollider2D>()->collidingColliders.size() != 0) {
					col->gameObject->GetComponent<SquareMovement>()->combineReady = true;
				}
			}
		}
	}
}