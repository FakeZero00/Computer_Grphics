#include "childSquare.h"
#include "Object.h"
#include "MeshRenderer2D.h"
#include <iostream>

childSquare::childSquare(InputManager& inputManager) : inputManager(inputManager) {
	Expose("isSelected", &isSelected);
}

void childSquare::Awake() {
	boxCollider = gameObject->GetComponent<BoxCollider2D>();
}

void childSquare::Update(float deltaTime) {
	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		cout << "Mouse Clicked at: (" << inputManager.GetMouseX() << ", " << inputManager.GetMouseY() << ")" << endl;
		if (boxCollider->Contains(inputManager.GetMouseX(), inputManager.GetMouseY())) {
			isSelected = !isSelected;
		}
	}

	if (isSelected){
		gameObject->GetComponent<MeshRenderer2D>()->isOutline = true;
	}
	else
		gameObject->GetComponent<MeshRenderer2D>()->isOutline = false;
}