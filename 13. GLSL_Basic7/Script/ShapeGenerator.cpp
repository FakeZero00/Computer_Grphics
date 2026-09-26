#include "ShapeGenerator.h"
#include "InputManager.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "BoxCollider.h"
#include "Spline.h"
#include <ranges>
using namespace std;

extern map<string, GLuint> shaders;

#include "Shape.h"

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	
	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		for (auto& obj : generatedObjects | views::reverse) {
			obj->GetComponent<Shape>()->Deselect();
		}

		for (auto& obj : generatedObjects | views::reverse) {
			BoxCollider* col = obj->GetComponent<BoxCollider>();
			if (col->MouseCollide(vec2(inputManager.GetMouseX(), inputManager.GetMouseY()))) {
				cout << "Clicked on object: " << obj->name << endl;
				obj->GetComponent<Shape>()->Select();
				break;
			}
		}
	}
	
	if (inputManager.GetKeyDown(GLFW_KEY_1) ||
		inputManager.GetKeyDown(GLFW_KEY_2) ||
		inputManager.GetKeyDown(GLFW_KEY_3) ||
		inputManager.GetKeyDown(GLFW_KEY_4)) {
		for (auto& obj : generatedObjects | views::reverse) {
			obj->GetComponent<Shape>()->Select();
		}
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_C)) {
		for (auto& obj : generatedObjects | views::reverse) {
			obj->Destroy();
		}
		generatedObjects.clear();
	}

	if (generatedObjects.size() < 50) {
		if (inputManager.GetKeyDown(GLFW_KEY_P)) {
			Object* newObject = gameObject->Instantiate("Point");
			MeshRenderer3D* mr = newObject->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
			mr->materials[0]->SetVec4("tColor", vec4(urdColor(dre), urdColor(dre), urdColor(dre), 1.0f));
			mr->materials[0]->isOutline = false;
			Transform* tr = newObject->GetComponent<Transform>();
			tr->SetLocalPosition(urd(dre), urd(dre), 0);
			tr->SetLocalScale(0.1f, 0.1f, 0.0f);
			BoxCollider* col = newObject->AddComponent<BoxCollider>();
			//col->isDebug = true;
			newObject->AddComponent<Shape>();

			generatedObjects.push_back(newObject);
		}

		else if (inputManager.GetKeyDown(GLFW_KEY_E)) {
			Object* newObject = gameObject->Instantiate("Line");
			float randX = urdLine(dre);
			float randY = urdLine(dre);
			vector<vec3> controlPoints = {
				vec3(randX, randY, 0),
				vec3(-randX, -randY, 0)
			};
			Spline* sp = newObject->AddComponent<Spline>(controlPoints, vec4{urdColor(dre), urdColor(dre), urdColor(dre), 1.0f});
			Transform* tr = newObject->GetComponent<Transform>();
			tr->SetLocalPosition(urd(dre), urd(dre), 0);
			BoxCollider* col = newObject->AddComponent<BoxCollider>();
			col->size.x = (std::max(randX, -randX) - std::min(randX, -randX));
			col->size.y = (std::max(randY, -randY) - std::min(randY, -randY));
			newObject->AddComponent<Shape>();

			generatedObjects.push_back(newObject);
		}

		else if (inputManager.GetKeyDown(GLFW_KEY_T)) {
			Object* newObject = gameObject->Instantiate("Triangle");
			MeshRenderer3D* mr = newObject->AddComponent<MeshRenderer3D>(isoPolyMesh, new Material{ shaders["Standard"] });
			mr->materials[0]->SetVec4("tColor", vec4(urdColor(dre), urdColor(dre), urdColor(dre), 1.0f));
			mr->materials[0]->isOutline = false;
			Transform* tr = newObject->GetComponent<Transform>();
			tr->SetLocalPosition(urd(dre), urd(dre), 0);
			tr->SetLocalScale(urdScale(dre), urdScale(dre), 0.0f);
			BoxCollider* col = newObject->AddComponent<BoxCollider>();
			//col->isDebug = true;
			newObject->AddComponent<Shape>();

			generatedObjects.push_back(newObject);
		}

		else if (inputManager.GetKeyDown(GLFW_KEY_R)) {
			Object* newObject = gameObject->Instantiate("Rectangle");
			MeshRenderer3D* mr = newObject->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
			mr->materials[0]->SetVec4("tColor", vec4(urdColor(dre), urdColor(dre), urdColor(dre), 1.0f));
			mr->materials[0]->isOutline = false;
			Transform* tr = newObject->GetComponent<Transform>();
			tr->SetLocalPosition(urd(dre), urd(dre), 0);
			tr->SetLocalScale(urdScale(dre), urdScale(dre), 0.0f);
			BoxCollider* col = newObject->AddComponent<BoxCollider>();
			//col->isDebug = true;
			newObject->AddComponent<Shape>();

			generatedObjects.push_back(newObject);
		}
	}
}