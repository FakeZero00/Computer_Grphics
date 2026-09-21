#include "NewSquare.h"
#include "BoxCollider2D.h"

void NewSquare::Update(float deltaTime) {
	if (timer > 0.0f) timer -= deltaTime;
	else if (timer <= 0.0f) {
		if (!gameObject->GetComponent<BoxCollider2D>())
			gameObject->AddComponent<BoxCollider2D>(0.1f, 0.1f);
	}
}