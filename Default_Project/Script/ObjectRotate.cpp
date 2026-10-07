#include "ObjectRotate.h"
#include "Object.h"
#include "Transform.h"

void ObjectRotate::Update(float deltaTime) {
	Transform* tr = gameObject->GetComponent<Transform>();

	tr->Rotate(0.0f, speed * deltaTime, 0.0f);
}