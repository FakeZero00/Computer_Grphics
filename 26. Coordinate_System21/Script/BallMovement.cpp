#include "BallMovement.h"
#include "Object.h"

void BallMovement::Start() {
	tr = gameObject->GetComponent<Transform>();
	velocity = vec3(urd(dre), urd(dre), 0.0f);
}

void BallMovement::Update(float deltaTime) {
	Transform* tr = gameObject->GetComponent<Transform>();
	
	tr->Translate(velocity.x * deltaTime, velocity.y * deltaTime, 0.0f);

	if (tr->position.x < -5.0f + radius || tr->position.x > 5.0f - radius) {
		velocity.x = -velocity.x;
	}
	if (tr->position.y < -5.0f + radius || tr->position.y > 5.0f - radius) {
		velocity.y = -velocity.y;
	}
}

Component* BallMovement::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	BallMovement* ballMovement = obj->AddComponent<BallMovement>();

	return ballMovement;
}

REGISTER_COMPONENT(BallMovement);