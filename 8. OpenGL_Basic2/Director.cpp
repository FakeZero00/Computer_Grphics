#include "Director.h"
#include <string>
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer2D.h"
#include "BoxCollider2D.h"
#include "childSquare.h"

Director::Director(InputManager& inputMgr) : inputManager(inputMgr) {
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
			cSquare->AddComponent<childSquare>(inputManager);
			counter1++;
			size1 -= 0.1f;
		}
	}
}