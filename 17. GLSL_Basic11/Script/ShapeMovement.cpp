#include "ShapeMovement.h"
#include "InputManager.h"
#include "Object.h"
#include "Material.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Spline.h"
#include "MeshRenderer3D.h"
#include <iostream>
using namespace std;

#include "ShapeGenerator.h"

void ShapeMovement::SafeDestroy() {
	shapeGenerator->generatedObjects.erase(remove(shapeGenerator->generatedObjects.begin(), shapeGenerator->generatedObjects.end(), gameObject), shapeGenerator->generatedObjects.end());
	gameObject->Destroy();
}

void ShapeMovement::OnTriggerStay(Object* other) {
	InputManager inputManager = gameObject->ctx.inputManager;
	BoxCollider* col;
	MeshRenderer3D* mr;
	Transform* tr;
	if (!isMoving) {
		if (gameObject->name == "regularPolygon" && other->name == "regularPolygonCol" ||
			gameObject->name == "rightPolygon" && other->name == "rightPolygonCol" ||
			gameObject->name == "rectangle" && other->name == "rectangleCol") {
			col = other->GetComponent<BoxCollider>();
			if (col->MouseCollide(vec2{ inputManager.GetMouseX(), inputManager.GetMouseY() })) {
				tr = other->GetComponent<Transform>();
				if (gameObject->GetComponent<Transform>()->rotation == tr->rotation) {
					mr = other->GetComponent<MeshRenderer3D>();
					vec4 color = gameObject->GetComponent<MeshRenderer3D>()->materials[0]->GetVec4("tColor");
					mr->materials[0]->SetVec4("tColor", color);
					SafeDestroy();
				}
			}
		}
	}
}

void ShapeMovement::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	Transform* tr = gameObject->GetComponent<Transform>();

	if (isMoving) {
		tr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
	}
}