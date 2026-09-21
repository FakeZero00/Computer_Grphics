#include "SquareSpawner.h"
#include <random>
#include "Object.h"
#include "Particle.h"

void SquareSpawner::Execute() {
	random_device rd;
	default_random_engine dre{ rd() };
	uniform_int_distribution<int> uid {0, 3};

	int moveType = uid(dre);
	Transform* tr = gameObject->GetComponent<Transform>();
	MeshRenderer2D* renderer = gameObject->GetComponent<MeshRenderer2D>();

	if (moveType == 0) {
		Object* Particle1 = SpawnParticle(renderer, 0.0f, 0.01f, 2.0f, 0.0f, 1.0f);
		Object* Particle2 = SpawnParticle(renderer, 0.01f, 0.0f, 2.0f, 1.0f, 0.0f);
		Object* Particle3 = SpawnParticle(renderer, 0.0f, -0.01f, 2.0f, 0.0f, -1.0f);
		Object* Particle4 = SpawnParticle(renderer, -0.01f, 0.0f, 2.0f, -1.0f, 0.0f);
	}
	else if (moveType == 1) {
		Object* Particle1 = SpawnParticle(renderer, 0.01f, 0.01f, 2.0f, 1.0f, 1.0f);
		Object* Particle2 = SpawnParticle(renderer, 0.01f, -0.01f, 2.0f, 1.0f, -1.0f);
		Object* Particle3 = SpawnParticle(renderer, -0.01f, -0.01f, 2.0f, -1.0f, -1.0f);
		Object* Particle4 = SpawnParticle(renderer, -0.01f, 0.01f, 2.0f, -1.0f, 1.0f);
	}
	else if (moveType == 2){
		float resizedWidth = renderer->width / 4.0f;
		float resizedHeight = renderer->height / 4.0f;

		uniform_real_distribution urd{ -1.0f, 1.0f };
		float directionX = urd(dre);
		float directionY = urd(dre);

		Object* Particle1 = SpawnParticle(renderer, resizedWidth, resizedHeight, 2.5f, directionX, directionY, true);
		Object* Particle2 = SpawnParticle(renderer, -resizedWidth, resizedHeight, 2.5f, directionX, directionY, true);
		Object* Particle3 = SpawnParticle(renderer, -resizedWidth, -resizedHeight, 2.5f, directionX, directionY, true);
		Object* Particle4 = SpawnParticle(renderer, resizedWidth, -resizedHeight, 2.5f, directionX, directionY, true);
	}
	else if (moveType == 3) {
		Object* Particle1 = SpawnParticle(renderer, 0.01f, 0.01f, 3.0f, 1.0f, 1.0f);
		Object* Particle2 = SpawnParticle(renderer, 0.01f, 0.00f, 3.0f, 1.0f, 0.0f);
		Object* Particle3 = SpawnParticle(renderer, 0.01f, -0.01f, 3.0f, 1.0f, -1.0f);
		Object* Particle4 = SpawnParticle(renderer, 0.0f, -0.01f, 3.0f, 0.0f, -1.0f);
		Object* Particle5 = SpawnParticle(renderer, -0.01f, -0.01f, 3.0f, -1.0f, -1.0f);
		Object* Particle6 = SpawnParticle(renderer, -0.01f, 0.0f, 3.0f, -1.0f, 0.0f);
		Object* Particle7 = SpawnParticle(renderer, -0.01f, 0.01f, 3.0f, -1.0f, 1.0f);
		Object* Particle8 = SpawnParticle(renderer, 0.0f, 0.01f, 3.0f, 0.0f, 1.0f);
	}

	gameObject->Destroy();
}

Object* SquareSpawner::SpawnParticle(MeshRenderer2D* renderer, float offsetX, float offsetY, float count, float vx, float vy, bool outline) {
	Transform* tr = gameObject->GetComponent<Transform>();

	Object* particle = tr->parent->gameObject->Instantiate("Particle");
	particle->AddComponent<MeshRenderer2D>(renderer->width / count, renderer->height / count, renderer->color);
	particle->GetComponent<MeshRenderer2D>()->isOutline = outline;

	
	Transform* particleTr = particle->GetComponent<Transform>();
	particleTr->SetLocalPosition(tr->position.x + offsetX, tr->position.y + offsetY, tr->position.z);

	float addedColor = renderer->color.r + renderer->color.g + renderer->color.b;
	bool toLight = addedColor < 1.5f;

	particle->AddComponent<Particle>(vx, vy, toLight);

	return particle;
}