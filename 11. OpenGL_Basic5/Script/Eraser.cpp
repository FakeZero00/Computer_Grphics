#include "Eraser.h"
#include "InputManager.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer2D.h"

void Eraser::OnTriggerEnter(Object* other) {
	Transform* tr = gameObject->GetComponent<Transform>();
	MeshRenderer2D* renderer = gameObject->GetComponent<MeshRenderer2D>();

	renderer->color = other->GetComponent<MeshRenderer2D>()->color;
	tr->scale.x += 0.05f;
	tr->scale.y += 0.05f;

	other->isValid = false;
}

void Eraser::Update(float deltaTime) {
	Transform* tr = gameObject->GetComponent<Transform>();
	InputManager inputManager = gameObject->ctx.inputManager;

	tr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), tr->position.z);
}