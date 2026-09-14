#include "DirectorScript.h"
#include "Object.h"
#include "AppContext.h"
#include "Transform.h"
#include "InputManager.h"
#include "MeshRenderer2D.h"
#include <random>

void DirectorScript::Update(float deltaTime) {
	InputManager& inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_A)) {
		if (Squares.size() < 10) {
			random_device rd;
			default_random_engine dre{ rd() };
			uniform_real_distribution<float> urd{ -0.7f, 0.7f };
			uniform_real_distribution<float> urd2{ 0.0f, 1.0f };
			uniform_real_distribution<float> urd3{ 0.1f, 0.3f };

			Object* nSquare = gameObject->Instantiate("Square");
			Transform* nSquareTr = nSquare->GetComponent<Transform>();
			nSquareTr->SetLocalPosition(urd(dre), urd(dre), 0.0f);
			float size = urd3(dre);
			MeshRenderer2D* nSquareMR = nSquare->AddComponent<MeshRenderer2D>(size, size, Color{urd2(dre), urd2(dre), urd2(dre), 1.0f});
			Squares.push_back(nSquare);
		}
	}
}