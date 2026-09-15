#include "SquareMovement.h"
#include "Transform.h"
#include "Object.h"
#include "BoxCollider2D.h"
#include "InputManager.h"

void SquareMovement::Update(float deltaTime) {
	if (isMoving) {
		Transform* tr = gameObject->GetComponent<Transform>();
		BoxCollider2D* bc = gameObject->GetComponent<BoxCollider2D>();
		InputManager& inputManager = gameObject->ctx.inputManager;

		tr->position.x = inputManager.GetMouseX();
		tr->position.y = inputManager.GetMouseY();

		tr->CalculateWorldPosition();
		bc->RecalculateCollision();
	}
}