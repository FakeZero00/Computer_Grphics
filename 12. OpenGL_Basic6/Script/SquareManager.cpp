#include "SquareManager.h"
#include <Object.h>
#include <random>
#include <ranges>
#include "MeshRenderer2D.h"
#include "InputManager.h"
using namespace std;

#include "SquareSpawner.h"

void SquareManager::Start() {
	random_device rd;
	default_random_engine dre{ rd()};
	uniform_int_distribution uid{ 5, 10 };
	uniform_real_distribution urd{ 0.1f, 0.3f };
	uniform_real_distribution urd2{ 0.0f, 1.0f };

	for (int i = 0; i < uid(dre); ++i) {
		float size = urd(dre);

		Object* square = gameObject->Instantiate("Square");
		Transform* tr = square->GetComponent<Transform>();
		square->AddComponent<MeshRenderer2D>(size, size, Color{urd2(dre), urd2(dre), urd2(dre), 1.0f});
		square->AddComponent<BoxCollider2D>(size, size);

		uniform_real_distribution urdPos{ -1.0f + size / 2.0f, 1.0f - size / 2.0f };
		tr->SetLocalPosition(urdPos(dre), urdPos(dre), 0.0f);

		square->AddComponent<SquareSpawner>();
	}
}

void SquareManager::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	for (auto& objTr : gameObject->GetComponent<Transform>()->children | views::reverse) {
		if (!objTr->gameObject->GetComponent<BoxCollider2D>()) continue;
		BoxCollider2D* col = objTr->gameObject->GetComponent<BoxCollider2D>();

		if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
			float mouseX = inputManager.GetMouseX();
			float mouseY = inputManager.GetMouseY();
			if (col->Contains(mouseX, mouseY)) {
				if(objTr->gameObject->GetComponent<SquareSpawner>())
					objTr->gameObject->GetComponent<SquareSpawner>()->Execute();
				break;
			}
		}
	}
}