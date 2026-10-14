#include <MoonOrbit.h>
#include "Object.h"

void MoonOrbit::Start() {
	tr = gameObject->GetComponent<Transform>();
}

void MoonOrbit::Update(float deltaTime) {
	float rotationSpeed = 20.0f; //회전 속도
	tr->Rotate(0.0f, rotationSpeed * deltaTime, 0.0f);
}