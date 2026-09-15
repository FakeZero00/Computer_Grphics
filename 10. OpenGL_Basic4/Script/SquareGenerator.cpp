#include "SquareGenerator.h"
#include "InputManager.h"
#include "Object.h"
#include "MeshRenderer2D.h"
#include <random>

#include "SquareMovement.h"

void SquareGenerator::CreateSquare() {
	InputManager& inputManager = gameObject->ctx.inputManager;

	random_device rd;
	default_random_engine dre{ rd()};
	uniform_real_distribution<float> urd{ 0.0f, 1.0f };

	cout << gameObject->GetComponent<Transform>()->children.size() << endl;
	if (gameObject->GetComponent<Transform>()->children.size() < 5) {
		cout << "Spawned" << endl;
		Object* nSquare = gameObject->Instantiate("Square");
		Transform* nSquareTr = nSquare->GetComponent<Transform>();
		MeshRenderer2D* nSquareMr = nSquare->AddComponent<MeshRenderer2D>();

		nSquareTr->position.x = inputManager.GetMouseX();
		nSquareTr->position.y = inputManager.GetMouseY();
		nSquareTr->CalculateWorldPosition();

		nSquareMr->SetSize(width, height);
		nSquareMr->color = Color{ urd(dre), urd(dre), urd(dre), 1.0f};

		nSquare->AddComponent<SquareMovement>();
	}
}

void SquareGenerator::Update(float deltaTime) {
	InputManager& inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) CreateSquare();
}