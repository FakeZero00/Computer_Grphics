#include "ShapeGenerator.h"
#include "InputManager.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "BoxCollider.h"
#include "Spline.h"
#include <string>
#include <ranges>
using namespace std;

#include "ShapeMovement.h"

extern map<string, GLuint> shaders;

Object* ShapeGenerator::createShape(string name, bool isLeft) {
	Object* obj = gameObject->Instantiate(name);
	MeshRenderer3D* mr = obj->AddComponent<MeshRenderer3D>(rectMesh, new Material(shaders["Standard"]));
	mr->materials[0]->SetVec4("tColor", vec4{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f });
	BoxCollider* col = obj->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f });

	Transform* tr = obj->GetComponent<Transform>();
	if (isLeft) tr->SetLocalPosition(spawnPosL, -0.7f, 0.0f);
	else tr->SetLocalPosition(spawnPosR, 0.7f, 0.0f);

	ShapeMovement* sm = obj->AddComponent<ShapeMovement>(urdSpd(dre), urdColor(dre) <= 0.5f ? 1.0f : -1.0f);

	return obj;
}

void ShapeGenerator::Start() {
	cout << "ShapeGenerator Started" << endl;

	shapeL = createShape("ShapeL", true);
	shapeR = createShape("ShapeR", false);
}

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	ShapeMovement* smL = shapeL->GetComponent<ShapeMovement>();
	ShapeMovement* smR = shapeR->GetComponent<ShapeMovement>();
	
	if (inputManager.GetKeyDown(GLFW_KEY_ENTER)) {
		if (smL->isBorder && smR->isBorder) {
			smL->isEnter = true;
			smR->isEnter = true;

			smL->speed = 1.5f;
			smR->speed = 1.5f;

			shapes.push_back(shapeL);
			shapes.push_back(shapeR);

			shapeL = createShape("ShapeL", true);
			shapeR = createShape("ShapeR", false);
		}
	}

	if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		shapeL->Destroy();
		shapeR->Destroy();
		
		for (auto& shape : shapes) shape->Destroy();
		shapes.clear();
		
		shapeL = createShape("ShapeL", true);
		shapeR = createShape("ShapeR", false);
	}

	for (int i = 0; i < shapes.size(); i++) {
		Object* shape = shapes[i];
		Transform* tr = shape->GetComponent<Transform>();
		tr->SetLocalScale(0.3f, 0.3f, 1.0f);

		ShapeMovement* sm = shape->GetComponent<ShapeMovement>();
		sm->destPos = vec3{ 0.7f, -0.95f + 0.05f * i, 0.0f };
	}
}