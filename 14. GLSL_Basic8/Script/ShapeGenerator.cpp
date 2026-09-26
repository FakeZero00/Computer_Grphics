#include "ShapeGenerator.h"
#include "InputManager.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "BoxCollider.h"
#include "Spline.h"
#include "Object.h"
using namespace std;

extern map<string, GLuint> shaders;

void ShapeGenerator::Start() {
	for (int i = 1; i <= 4; ++i) {
		Object* newObj = gameObject->Instantiate("isoPolygon_Mesh");
		MeshRenderer3D* mr = newObj->AddComponent<MeshRenderer3D>(isoPolyMesh, new Material{ shaders["Standard"] });
		newObj->isValid = false;

		Object* newSpline = gameObject->Instantiate("isoPolygon_Spline");
		newSpline->AddComponent<Spline>(isoPolyvert, vec4{ 0.0, 0.0, 0.0, 1.0 });
		newSpline->isValid = false;

		if (i == 1) {
			obj1[0] = newObj;
			obj1[1] = newSpline;
		}
		else if (i == 2) {
			obj2[0] = newObj;
			obj2[1] = newSpline;
		}
		else if (i == 3) {
			obj3[0] = newObj;
			obj3[1] = newSpline;
		}
		else if (i == 4) {
			obj4[0] = newObj;
			obj4[1] = newSpline;
		}
	}
}

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	
	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		vec4 color{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f };
		float scale = urdScale(dre);

		//1사분면
		if (inputManager.GetMouseX() >= 0.0f &&
			inputManager.GetMouseY() >= 0.0f) {
			if (isLineMode) {
				obj1[0]->isValid = false;
				obj1[1]->isValid = true;
			}
			else {
				obj1[0]->isValid = true;
				obj1[1]->isValid = false;
			}

			Transform* objTr = obj1[0]->GetComponent<Transform>();
			Transform* splineTr = obj1[1]->GetComponent<Transform>();
			objTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			splineTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			objTr->SetLocalScale(scale, scale, 0.0f);
			splineTr->SetLocalScale(scale, scale, 0.0f);

			MeshRenderer3D* objmr = obj1[0]->GetComponent<MeshRenderer3D>();
			Spline* splinemr = obj1[1]->GetComponent<Spline>();
			objmr->materials[0]->SetVec4("tColor", color);
			splinemr->SetColor(color);
		}
		
		//2사분면
		else if (inputManager.GetMouseX() < 0.0f &&
			inputManager.GetMouseY() >= 0.0f) {
			if (isLineMode) {
				obj2[0]->isValid = false;
				obj2[1]->isValid = true;
			}
			else {
				obj2[0]->isValid = true;
				obj2[1]->isValid = false;
			}
			Transform* objTr = obj2[0]->GetComponent<Transform>();
			Transform* splineTr = obj2[1]->GetComponent<Transform>();
			objTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			splineTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			objTr->SetLocalScale(scale, scale, 0.0f);
			splineTr->SetLocalScale(scale, scale, 0.0f);

			MeshRenderer3D* objmr = obj2[0]->GetComponent<MeshRenderer3D>();
			Spline* splinemr = obj2[1]->GetComponent<Spline>();
			objmr->materials[0]->SetVec4("tColor", color);
			splinemr->SetColor(color);
		}

		//3사분면
		else if (inputManager.GetMouseX() < 0.0f &&
			inputManager.GetMouseY() < 0.0f) {
			if (isLineMode) {
				obj3[0]->isValid = false;
				obj3[1]->isValid = true;
			}
			else {
				obj3[0]->isValid = true;
				obj3[1]->isValid = false;
			}
			Transform* objTr = obj3[0]->GetComponent<Transform>();
			Transform* splineTr = obj3[1]->GetComponent<Transform>();
			objTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			splineTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			objTr->SetLocalScale(scale, scale, 0.0f);
			splineTr->SetLocalScale(scale, scale, 0.0f);

			MeshRenderer3D* objmr = obj3[0]->GetComponent<MeshRenderer3D>();
			Spline* splinemr = obj3[1]->GetComponent<Spline>();
			objmr->materials[0]->SetVec4("tColor", color);
			splinemr->SetColor(color);
		}

		//4사분면
		else if (inputManager.GetMouseX() >= 0.0f &&
			inputManager.GetMouseY() < 0.0f) {
			if (isLineMode) {
				obj4[0]->isValid = false;
				obj4[1]->isValid = true;
			}
			else {
				obj4[0]->isValid = true;
				obj4[1]->isValid = false;
			}
			Transform* objTr = obj4[0]->GetComponent<Transform>();
			Transform* splineTr = obj4[1]->GetComponent<Transform>();
			objTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			splineTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
			objTr->SetLocalScale(scale, scale, 0.0f);
			splineTr->SetLocalScale(scale, scale, 0.0f);

			MeshRenderer3D* objmr = obj4[0]->GetComponent<MeshRenderer3D>();
			Spline* splinemr = obj4[1]->GetComponent<Spline>();
			objmr->materials[0]->SetVec4("tColor", color);
			splinemr->SetColor(color);
		}
	}

	else if (inputManager.GetKeyPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		//1사분면 축소, 확대
		if (inputManager.GetMouseX() >= 0.0f &&
			inputManager.GetMouseX() < 0.5f &&
			inputManager.GetMouseY() >= 0.0f) {
			Transform* objTr = obj1[0]->GetComponent<Transform>();
			Transform* splineTr = obj1[1]->GetComponent<Transform>();
			if (objTr->scale.x > 0.2f) {
				objTr->SetLocalScale(objTr->scale.x - 0.1f, objTr->scale.y - 0.1f, 0.0f);
				splineTr->SetLocalScale(splineTr->scale.x - 0.1f, splineTr->scale.y - 0.1f, 0.0f);
			}
		}
		else if (inputManager.GetMouseX() >= 0.5f &&
			inputManager.GetMouseX() < 1.0f &&
			inputManager.GetMouseY() >= 0.0f) {
			Transform* objTr = obj1[0]->GetComponent<Transform>();
			Transform* splineTr = obj1[1]->GetComponent<Transform>();
			if (objTr->scale.x < 5.0f) {
				objTr->SetLocalScale(objTr->scale.x + 0.1f, objTr->scale.y + 0.1f, 0.0f);
				splineTr->SetLocalScale(splineTr->scale.x + 0.1f, splineTr->scale.y + 0.1f, 0.0f);
			}
		}
		
		//2사분면 축소, 확대
		else if (inputManager.GetMouseX() >= -1.0f &&
			inputManager.GetMouseX() < -0.5f &&
			inputManager.GetMouseY() >= 0.0f) {
			Transform* objTr = obj2[0]->GetComponent<Transform>();
			Transform* splineTr = obj2[1]->GetComponent<Transform>();
			if (objTr->scale.x > 0.2f) {
				objTr->SetLocalScale(objTr->scale.x - 0.1f, objTr->scale.y - 0.1f, 0.0f);
				splineTr->SetLocalScale(splineTr->scale.x - 0.1f, splineTr->scale.y - 0.1f, 0.0f);
			}
		}
		else if (inputManager.GetMouseX() >= -0.5f &&
			inputManager.GetMouseX() < 0.0f &&
			inputManager.GetMouseY() >= 0.0f) {
			Transform* objTr = obj2[0]->GetComponent<Transform>();
			Transform* splineTr = obj2[1]->GetComponent<Transform>();
			if (objTr->scale.x < 5.0f) {
				objTr->SetLocalScale(objTr->scale.x + 0.1f, objTr->scale.y + 0.1f, 0.0f);
				splineTr->SetLocalScale(splineTr->scale.x + 0.1f, splineTr->scale.y + 0.1f, 0.0f);
			}
		}

		//3사분면 축소, 확대
		else if (inputManager.GetMouseX() >= -1.0f &&
			inputManager.GetMouseX() < -0.5f &&
			inputManager.GetMouseY() < 0.0f) {
			Transform* objTr = obj3[0]->GetComponent<Transform>();
			Transform* splineTr = obj3[1]->GetComponent<Transform>();
			if (objTr->scale.x > 0.2f) {
				objTr->SetLocalScale(objTr->scale.x - 0.1f, objTr->scale.y - 0.1f, 0.0f);
				splineTr->SetLocalScale(splineTr->scale.x - 0.1f, splineTr->scale.y - 0.1f, 0.0f);
			}
		}
		else if (inputManager.GetMouseX() >= -0.5f &&
			inputManager.GetMouseX() < 0.0f &&
			inputManager.GetMouseY() < 0.0f) {
			Transform* objTr = obj3[0]->GetComponent<Transform>();
			Transform* splineTr = obj3[1]->GetComponent<Transform>();
			if (objTr->scale.x < 5.0f) {
				objTr->SetLocalScale(objTr->scale.x + 0.1f, objTr->scale.y + 0.1f, 0.0f);
				splineTr->SetLocalScale(splineTr->scale.x + 0.1f, splineTr->scale.y + 0.1f, 0.0f);
			}
		}

		//4사분면 축소, 확대
		else if (inputManager.GetMouseX() >= 0.0f &&
			inputManager.GetMouseX() < 0.5f &&
			inputManager.GetMouseY() < 0.0f) {
			Transform* objTr = obj4[0]->GetComponent<Transform>();
			Transform* splineTr = obj4[1]->GetComponent<Transform>();
			if (objTr->scale.x > 0.2f) {
				objTr->SetLocalScale(objTr->scale.x - 0.1f, objTr->scale.y - 0.1f, 0.0f);
				splineTr->SetLocalScale(splineTr->scale.x - 0.1f, splineTr->scale.y - 0.1f, 0.0f);
			}
		}
		else if (inputManager.GetMouseX() >= 0.5f &&
			inputManager.GetMouseX() < 1.0f &&
			inputManager.GetMouseY() < 0.0f) {
			Transform* objTr = obj4[0]->GetComponent<Transform>();
			Transform* splineTr = obj4[1]->GetComponent<Transform>();
			if (objTr->scale.x < 5.0f) {
				objTr->SetLocalScale(objTr->scale.x + 0.1f, objTr->scale.y + 0.1f, 0.0f);
				splineTr->SetLocalScale(splineTr->scale.x + 0.1f, splineTr->scale.y + 0.1f, 0.0f);
			}
		}
	}

	else if (inputManager.GetKeyDown(GLFW_KEY_A)) {
		isLineMode = false;

		obj1[0]->isValid = true;
		obj1[1]->isValid = false;

		obj2[0]->isValid = true; 
		obj2[1]->isValid = false;

		obj3[0]->isValid = true; 
		obj3[1]->isValid = false;

		obj4[0]->isValid = true; 
		obj4[1]->isValid = false;
	}

	else if (inputManager.GetKeyDown(GLFW_KEY_B)) {
		isLineMode = true;

		obj1[0]->isValid = false;
		obj1[1]->isValid = true;

		obj2[0]->isValid = false;
		obj2[1]->isValid = true;

		obj3[0]->isValid = false;
		obj3[1]->isValid = true;

		obj4[0]->isValid = false;
		obj4[1]->isValid = true;
	}

	else if (inputManager.GetKeyDown(GLFW_KEY_C)) {
		obj1[0]->isValid = false;
		obj1[1]->isValid = false;

		obj2[0]->isValid = false;
		obj2[1]->isValid = false;

		obj3[0]->isValid = false;
		obj3[1]->isValid = false;

		obj4[0]->isValid = false;
		obj4[1]->isValid = false;
	}
}