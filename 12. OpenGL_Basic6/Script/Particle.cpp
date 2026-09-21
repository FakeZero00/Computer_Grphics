#include "Particle.h"
#include "Transform.h"
#include "MeshRenderer2D.h"
#include "Object.h"

void Particle::Update(float deltaTime) {
	Transform* tr = gameObject->GetComponent<Transform>();
	MeshRenderer2D* renderer = gameObject->GetComponent<MeshRenderer2D>();

	tr->Translate(velocity.x * deltaTime, velocity.y * deltaTime, 0.0f);

	float shrinkSpeed = 1.0f;
	tr->scale.x -= shrinkSpeed * deltaTime;
	tr->scale.y -= shrinkSpeed * deltaTime;

	float colorChangeSpeed = 0.8f;
	if (toLight) {
		renderer->color.r = min(renderer->color.r += colorChangeSpeed * deltaTime, 1.0f);
		renderer->color.g = min(renderer->color.g += colorChangeSpeed * deltaTime, 1.0f);
		renderer->color.b = min(renderer->color.b += colorChangeSpeed * deltaTime, 1.0f);
	}
	else {
		renderer->color.r = max(renderer->color.r -= colorChangeSpeed * deltaTime, 0.0f);
		renderer->color.g = max(renderer->color.g -= colorChangeSpeed * deltaTime, 0.0f);
		renderer->color.b = max(renderer->color.b -= colorChangeSpeed * deltaTime, 0.0f);
	}

	if (tr->scale.x <= 0.0f || tr->scale.y <= 0.0f) {
		gameObject->Destroy();
	}
	if (tr->worldPosition.x + renderer->width / 2.0f < -1.0f || tr->worldPosition.x - renderer->width / 2.0f > 1.0f ||
		tr->worldPosition.y + renderer->height / 2.0f < -1.0f || tr->worldPosition.y - renderer->height / 2.0f > 1.0f) {
		gameObject->Destroy();
	}
}