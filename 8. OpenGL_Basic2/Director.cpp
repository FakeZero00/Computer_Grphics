#include "Director.h"
#include <string>
#include <memory>
#include <ranges>
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer2D.h"
#include "BoxCollider2D.h"
#include "childSquare.h"

Director::Director(AppContext& ctx, InputManager& inputMgr) : context(ctx), inputManager(inputMgr) {
	Expose("Square1", &Square1);
	Expose("Square2", &Square2);
	Expose("Square3", &Square3);
	Expose("Square4", &Square4);
}

void Director::Update(float deltaTime) {
	if (inputManager.GetKeyDown(GLFW_KEY_1)) {
		if (counter1 < 5) {
			std::cout << Square1->name << std::endl;
			Object* cSquare = Square1->Instantiate(string{ "Square1 (" + std::to_string(counter1) + ")" });
			Transform* childTr = cSquare->GetComponent<Transform>();
			cSquare->AddComponent<MeshRenderer2D>(size1, size1, Color{ urd(dre), urd(dre), urd(dre), 1.0f });
			cSquare->AddComponent<BoxCollider2D>(size1, size1);
			context.CollisionObjects.push_back(cSquare);
			cSquare->AddComponent<childSquare>(context, inputManager);
			counter1++;
			size1 -= 0.1f;
		}
	}
	if (inputManager.GetKeyDown(GLFW_KEY_2)) {
		if (counter2 < 5) {
			std::cout << Square2->name << std::endl;
			Object* cSquare = Square2->Instantiate(string{ "Square2 (" + std::to_string(counter2) + ")" });
			Transform* childTr = cSquare->GetComponent<Transform>();
			cSquare->AddComponent<MeshRenderer2D>(size2, size2, Color{ urd(dre), urd(dre), urd(dre), 1.0f });
			cSquare->AddComponent<BoxCollider2D>(size2, size2);
			context.CollisionObjects.push_back(cSquare);
			cSquare->AddComponent<childSquare>(context, inputManager);
			counter2++;
			size2 -= 0.1f;
		}
	}
	if (inputManager.GetKeyDown(GLFW_KEY_3)) {
		if (counter3 < 5) {
			std::cout << Square3->name << std::endl;
			Object* cSquare = Square3->Instantiate(string{ "Square3 (" + std::to_string(counter3) + ")" });
			Transform* childTr = cSquare->GetComponent<Transform>();
			cSquare->AddComponent<MeshRenderer2D>(size3, size3, Color{ urd(dre), urd(dre), urd(dre), 1.0f });
			cSquare->AddComponent<BoxCollider2D>(size3, size3);
			context.CollisionObjects.push_back(cSquare);
			cSquare->AddComponent<childSquare>(context, inputManager);
			counter3++;
			size3 -= 0.1f;
		}
	}
	if (inputManager.GetKeyDown(GLFW_KEY_4)) {
		if (counter4 < 5) {
			std::cout << Square4->name << std::endl;
			Object* cSquare = Square4->Instantiate(string{ "Square4 (" + std::to_string(counter4) + ")" });
			Transform* childTr = cSquare->GetComponent<Transform>();
			cSquare->AddComponent<MeshRenderer2D>(size4, size4, Color{ urd(dre), urd(dre), urd(dre), 1.0f });
			cSquare->AddComponent<BoxCollider2D>(size4, size4);
			context.CollisionObjects.push_back(cSquare);
			cSquare->AddComponent<childSquare>(context, inputManager);
			counter4++;
			size4 -= 0.1f;
		}
	}

	if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		cout << "Resetting all squares..." << endl;
		for (auto& obj : Square1->GetComponent<Transform>()->children) {
			obj->gameObject->Destroy();
		}
		for (auto& obj : Square2->GetComponent<Transform>()->children) {
			obj->gameObject->Destroy();
		}
		for (auto& obj : Square3->GetComponent<Transform>()->children) {
			obj->gameObject->Destroy();
		}
		for (auto& obj : Square4->GetComponent<Transform>()->children) {
			obj->gameObject->Destroy();
		}

		Square1->GetComponent<Transform>()->children.clear();
		Square2->GetComponent<Transform>()->children.clear();
		Square3->GetComponent<Transform>()->children.clear();
		Square4->GetComponent<Transform>()->children.clear();
		
		counter1 = 0;
		counter2 = 0;
		counter3 = 0;
		counter4 = 0;

		size1 = 0.8f;
		size2 = 0.8f;
		size3 = 0.8f;
		size4 = 0.8f;
	}

	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		for (auto& obj : views::reverse(context.CollisionObjects)) {
			BoxCollider2D* collider = obj->GetComponent<BoxCollider2D>();
			if (collider && collider->Contains(inputManager.GetMouseX(), inputManager.GetMouseY())) {
				std::cout << "Clicked on: " << obj->name << std::endl;
				obj->GetComponent<childSquare>()->SetSelected();
				break;
			}
		}
	}
}