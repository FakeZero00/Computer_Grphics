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

void ShapeMovement::Update(float deltaTime) {
	Transform* tr = gameObject->GetComponent<Transform>();
	if (destPos == tr->position) isMove = false;

	if (isEnter && isMove) {
		vec3 dir = destPos - tr->position;
		tr->Translate(dir.x * speed * deltaTime, dir.y * speed * deltaTime, dir.z * speed * deltaTime);
	}
	if(isMove && !isEnter) tr->Translate(0.0f, direction * speed * deltaTime, 0.0f);
}

void ShapeMovement::OnTriggerEnter(Object* other) {
	if (other->name == "Border") isBorder = true;
	if (other->name == "BorderD") direction *= -1.0f;
}

void ShapeMovement::OnTriggerExit(Object* other) {
	if (other->name == "Border") isBorder = false;
}