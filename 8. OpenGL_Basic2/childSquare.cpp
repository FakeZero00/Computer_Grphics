#include "childSquare.h"
#include "Object.h"
#include "MeshRenderer2D.h"
#include <iostream>
#include <random>

childSquare::childSquare(AppContext& context, InputManager& inputManager) : context(context), inputManager(inputManager) {
	Expose("isSelected", &isSelected);
}

void childSquare::SetSelected() {
	isSelected = !isSelected;
}

void childSquare::Awake() {
	boxCollider = gameObject->GetComponent<BoxCollider2D>();
}

void childSquare::Update(float deltaTime) {
	if (isSelected){
		gameObject->GetComponent<MeshRenderer2D>()->isOutline = true;

		if (inputManager.GetKeyDown(GLFW_KEY_KP_ADD)) {
			MeshRenderer2D* meshRenderer = gameObject->GetComponent<MeshRenderer2D>();
			BoxCollider2D* boxCollider = gameObject->GetComponent<BoxCollider2D>();
			if (meshRenderer->width < 1.0f) {
				meshRenderer->SetSize(meshRenderer->width + 0.1f, meshRenderer->height + 0.1f);
				boxCollider->SetSize(boxCollider->width + 0.1f, boxCollider->height + 0.1f);
				boxCollider->RecalculateCollision();
			}
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_KP_SUBTRACT)) {
			MeshRenderer2D* meshRenderer = gameObject->GetComponent<MeshRenderer2D>();
			BoxCollider2D* boxCollider = gameObject->GetComponent<BoxCollider2D>();
			if (meshRenderer->width > 0.1f) {
				meshRenderer->SetSize(meshRenderer->width - 0.1f, meshRenderer->height - 0.1f);
				boxCollider->SetSize(boxCollider->width - 0.1f, boxCollider->height - 0.1f);
				boxCollider->RecalculateCollision();
			}
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_C)) {
			MeshRenderer2D* meshRenderer = gameObject->GetComponent<MeshRenderer2D>();
			
			random_device rd;
			default_random_engine dre{ rd() };
			uniform_real_distribution<float> urd{ 0.0f, 1.0f };

			meshRenderer->color = Color{ urd(dre), urd(dre), urd(dre), 1.0f };
		}
	}
	else
		gameObject->GetComponent<MeshRenderer2D>()->isOutline = false;
}