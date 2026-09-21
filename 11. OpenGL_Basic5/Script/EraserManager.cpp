#include "EraserManager.h"
#include "InputManager.h"
#include "Object.h"
#include "MeshRenderer2D.h"
#include "BoxCollider2D.h"
#include <random>
#include <string>

#include <NewSquare.h>

void EraserManager::CreateSquares() {
	random_device rd;
	default_random_engine dre{ rd() };
	uniform_int_distribution<int> uid{ 20, 40 };
	uniform_real_distribution<float> urd{ 0.0f, 1.0f };
	uniform_real_distribution<float> urdPos{ -0.9f, 0.9f };

	int count = 0;
	for (int i = 0; i < uid(dre); i++) {
		Object* square = gameObject->Instantiate("Square" + to_string(count++));
		square->AddComponent<MeshRenderer2D>(0.1f, 0.1f, Color{ urd(dre), urd(dre), urd(dre), 1.0f });
		square->AddComponent<BoxCollider2D>(0.1f, 0.1f);

		Transform* tr = square->GetComponent<Transform>();
		tr->SetLocalPosition(urdPos(dre), urdPos(dre), 0.0f);
	}
}

void EraserManager::Start() {
	CreateSquares();
}

void EraserManager::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		Transform* eraserTransform = eraserObject->GetComponent<Transform>();
		MeshRenderer2D* eraserRenderer = eraserObject->GetComponent<MeshRenderer2D>();

		eraserTransform->scale.x = 1.0f;
		eraserTransform->scale.y = 1.0f;
		eraserRenderer->color = { 0.0f, 0.0f, 0.0f, 1.0f };

		eraserTransform->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), eraserTransform->position.z);
		eraserObject->isValid = true;
	}

	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_RIGHT)) {
		cout << squares.size() << endl;
		if (eraserObject->isValid && squares.size() < 10) {
			random_device rd;
			default_random_engine dre{ rd() };
			uniform_real_distribution<float> urd{ 0.0f, 1.0f };

			Object* square = gameObject->Instantiate("Square");
			squares.push_back(square);
			Transform* tr = square->GetComponent<Transform>();
			MeshRenderer2D* renderer = square->AddComponent<MeshRenderer2D>(0.1f, 0.1f, Color{ urd(dre), urd(dre), urd(dre), 1.0f });

			tr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			square->AddComponent<NewSquare>();

			Transform* eraserTransform = eraserObject->GetComponent<Transform>();
			eraserTransform->scale.x -= 0.05f;
			eraserTransform->scale.y -= 0.05f;
		}
	}

	if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		for (auto& squares : gameObject->GetComponent<Transform>()->children) {
			squares->gameObject->Destroy();
		}

		CreateSquares();
	}

	if (inputManager.GetKeyUp(GLFW_MOUSE_BUTTON_LEFT)) {
		eraserObject->isValid = false;

		for (auto& child : gameObject->GetComponent<Transform>()->children) {
			child->gameObject->isValid = true;
		}

		for (auto& square : squares) {
			square->Destroy();
		}
		squares.clear();
	}
}