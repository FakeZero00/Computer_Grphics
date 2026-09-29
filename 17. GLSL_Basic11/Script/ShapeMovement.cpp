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
	InputManager inputManager = gameObject->ctx.inputManager;
	Transform* tr = gameObject->GetComponent<Transform>();
}