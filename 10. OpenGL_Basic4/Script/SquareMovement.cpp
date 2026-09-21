#include "SquareMovement.h"
#include "InputManager.h"
#include "Object.h"
#include "MeshRenderer2D.h"
#include <random>

void SquareMovement::Update(float deltaTime) {
	InputManager& inputManager = gameObject->ctx.inputManager;
	Transform* transform = gameObject->GetComponent<Transform>();
	MeshRenderer2D* renderer = gameObject->GetComponent<MeshRenderer2D>();

	if (inputManager.GetKeyDown(GLFW_KEY_1)) {
		if (MoveMode == 1) MoveMode = 0;
		else MoveMode = 1;

		if (clockmove == true) clockmove = false;

		random_device rd;
		default_random_engine dre{ rd() };
		uniform_real_distribution<float> urd{ -1.0f, 1.0f };

		velocity.x = urd(dre);
		velocity.y = urd(dre);
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_2)) {
		if (MoveMode == 2) MoveMode = 0;
		else MoveMode = 2;

		if (clockmove == true) clockmove = false;

		random_device rd;
		default_random_engine dre{ rd() };
		uniform_real_distribution<float> urd{ -1.0f, 1.0f };

		velocity.x = urd(dre);
		velocity.y = 0.0f;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_3)) {
		if (MoveMode == 3) MoveMode = 0;
		else MoveMode = 3;

		random_device rd;
		default_random_engine dre{ rd() };
		uniform_real_distribution<float> urd{ -1.0f, 1.0f };

		velocity.x = urd(dre);
		velocity.y = urd(dre);
	}

	transform->position.x += velocity.x * deltaTime;
	transform->position.y += velocity.y * deltaTime;

	if (MoveMode == 1 || MoveMode == 3 && clockmove == false ) {
		if (transform->position.x - (renderer->width / 2.0f) < -1.0f ||
			transform->position.x + (renderer->width / 2.0f) > 1.0f) {
			if (MoveMode == 3) clockmove = true;
			else velocity.x = -velocity.x;
		}
		if (transform->position.y - (renderer->height / 2.0f) < -1.0f ||
			transform->position.y + (renderer->height / 2.0f) > 1.0f) {
			if (MoveMode == 3) clockmove = true;
			else velocity.y = -velocity.y;
		}
	}
	else if (MoveMode == 2 && zigzag == false) {
		if (timer > 0.0f) {
			timer -= deltaTime;
			return;
		}
		else {
			velocity.x = 1.0f;
			velocity.y = 0.0f;
			timer = 0.0f;
		}
		if (transform->position.x - (renderer->width / 2.0f) < -1.0f ||
			transform->position.x + (renderer->width / 2.0f) > 1.0f) {
			velocity.x = -velocity.x;
		}
		else if (transform->position.x - (renderer->width / 2.0f) < -border) {
			velocity.x = 0.0f;
			velocity.y = 1.0f;
			timer = 0.1f;
		}
	}
	else if (MoveMode == 3 && clockmove == true) {
		if (transform->position.x + (renderer->width / 2.0f) > border &&
			transform->position.y + (renderer->height / 2.0f) > border) {
			velocity.x = -1.0f;
			velocity.y = 0.0f;
		}
		else if (transform->position.x - (renderer->width / 2.0f) < -border &&
			transform->position.y + (renderer->height / 2.0f) > border) {
			velocity.x = 0.0f;
			velocity.y = -1.0f;
		}
		else if (transform->position.x - (renderer->width / 2.0f) < -border &&
			transform->position.y - (renderer->height / 2.0f) < -border) {
			velocity.x = 1.0f;
			velocity.y = 0.0f;
		}
		else if (transform->position.x - (renderer->width / 2.0f) > border &&
			transform->position.y + (renderer->height / 2.0f) < -border) {
			velocity.x = 0.0f;
			velocity.y = 1.0f;
		}
		else if (transform->position.x - (renderer->width / 2.0f) < -border) {
			velocity.x = 0.0f;
			velocity.y = -1.0f;
		}
		else if (transform->position.x + (renderer->width / 2.0f) > border) {
			velocity.x = 0.0f;
			velocity.y = 1.0f;
		}
		else if (transform->position.y + (renderer->width / 2.0f) > border) {
			velocity.x = -1.0f;
			velocity.y = 0.0f;
		}
		else if (transform->position.y - (renderer->width / 2.0f) < -border) {
			velocity.x = 1.0f;
			velocity.y = 0.0f;
		}
	}
}