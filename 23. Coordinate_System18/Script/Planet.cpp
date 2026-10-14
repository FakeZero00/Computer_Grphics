#include <Planet.h>
#include "Object.h"

void Planet::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void Planet::Update(float deltaTime) {
	float rotationSpeed = 10.0f; //회전 속도
	tr->Rotate(-rotationSpeed * deltaTime, 0.0f, -rotationSpeed * deltaTime);
}