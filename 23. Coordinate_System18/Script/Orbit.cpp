#include <Orbit.h>
#include "Object.h"

void Orbit::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void Orbit::Update(float deltaTime) {
	float rotationSpeed = 20.0f; //회전 속도
	tr->Rotate(0.0f, rotationSpeed * deltaTime, 0.0f);
}