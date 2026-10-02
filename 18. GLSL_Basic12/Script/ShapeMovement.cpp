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

	tr->SetLocalScale(tr->scale.x + speed * deltaTime, tr->scale.y + speed * deltaTime, 0.0f);
	if (tr->scale.x > 15.0f) {
		gameObject->Destroy();
	}
}