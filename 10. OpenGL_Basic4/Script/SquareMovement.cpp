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

		if (transform->position.y - (renderer->height / 2.0f) <= -border) zigzag = false;
		else if (transform->position.y + (renderer->height / 2.0f) >= border) zigzag = true;

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
	else if (inputManager.GetKeyDown(GLFW_KEY_4)) {
		isScaling = !isScaling;
		upScaling = true;

		transform->scale.x = 1.0f;
		transform->scale.y = 1.0f;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_5)) {
		isColorChanging = !isColorChanging;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_S)) {
		transform->scale.x = 1.0f;
		transform->scale.y = 1.0f;

		MoveMode = 0;
		isScaling = false;
		isColorChanging = false;
	}

	if (isScaling) {
		float scaleSpeed = 0.5f;
		if (upScaling) {
			transform->scale.x += scaleSpeed * deltaTime;
			transform->scale.y += scaleSpeed * deltaTime;
		}
		else {
			transform->scale.x -= scaleSpeed * deltaTime;
			transform->scale.y -= scaleSpeed * deltaTime;
		}

		if (transform->scale.x >= 2.0f || transform->scale.y >= 2.0f) {
			upScaling = false;
		}
		else if (transform->scale.x <= 1.0f || transform->scale.y <= 1.0f) {
			upScaling = true;
		}
	}

	if (isColorChanging) {
		random_device rd;
		default_random_engine dre{ rd() };
		uniform_real_distribution<float> urd{ -1.0f, 1.0f };

		renderer->color = { urd(dre), urd(dre), urd(dre), 1.0f };
	}

	if (MoveMode == 0) return;

	if (timer > 0.0f && timerOn == true) {
		transform->position.y += velocity.y * deltaTime;
	}
	else {
		transform->position.x += velocity.x * deltaTime;
		transform->position.y += velocity.y * deltaTime;
	}

	if (MoveMode == 1 || MoveMode == 3 && clockmove == false) {
		if (transform->position.x - (renderer->width / 2.0f) <= -border ||
			transform->position.x + (renderer->width / 2.0f) >= border) {
			if (MoveMode == 3) clockmove = true;
			else velocity.x = -velocity.x;
		}
		if (transform->position.y - (renderer->height / 2.0f) <= -border ||
			transform->position.y + (renderer->height / 2.0f) >= border) {
			if (MoveMode == 3) clockmove = true;
			else velocity.y = -velocity.y;
		}
	}

	else if (MoveMode == 2) {
		float zigzagTime = 0.2f;

		if (timer > 0.0f) timer -= deltaTime;

		if (transform->position.x - (renderer->width / 2.0f) <= -border ||
			transform->position.x + (renderer->width / 2.0f) >= border) {
			velocity.x = -velocity.x;

			if (timer <= 0.0f && timerOn == false) {
				timer = zigzagTime;
				timerOn = true;

				if (zigzag == false) velocity.y = 1.0f;
				else velocity.y = -1.0f;
			}
			else if (timer <= 0.0f && timerOn == true) {
				velocity.y = 0;
				timer = 0.0f;
				timerOn = false;
			}
		}

		if (transform->position.y + (renderer->height / 2.0f) >= border) {
			zigzag = true;
			velocity.y = -velocity.y;
		}
		else if (transform->position.y - (renderer->height / 2.0f) <= -border) {
			zigzag = false;
			velocity.y = -velocity.y;
		}
	}

	else if (MoveMode == 3 && clockmove == true) {
		if (transform->position.x + (renderer->width / 2.0f) >= border &&
			transform->position.y + (renderer->height / 2.0f) >= border) {
			velocity.x = -1.0f;
			velocity.y = 0.0f;
		}
		else if (transform->position.x - (renderer->width / 2.0f) <= -border &&
			transform->position.y + (renderer->height / 2.0f) >= border) {
			velocity.x = 0.0f;
			velocity.y = -1.0f;
		}
		else if (transform->position.x - (renderer->width / 2.0f) <= -border &&
			transform->position.y - (renderer->height / 2.0f) <= -border) {
			velocity.x = 1.0f;
			velocity.y = 0.0f;
		}
		else if (transform->position.x - (renderer->width / 2.0f) >= border &&
			transform->position.y + (renderer->height / 2.0f) <= -border) {
			velocity.x = 0.0f;
			velocity.y = 1.0f;
		}
		else if (transform->position.x - (renderer->width / 2.0f) <= -border) {
			velocity.x = 0.0f;
			velocity.y = -1.0f;
		}
		else if (transform->position.x + (renderer->width / 2.0f) >= border) {
			velocity.x = 0.0f;
			velocity.y = 1.0f;
		}
		else if (transform->position.y + (renderer->width / 2.0f) >= border) {
			velocity.x = -1.0f;
			velocity.y = 0.0f;
		}
		else if (transform->position.y - (renderer->width / 2.0f) <= -border) {
			velocity.x = 1.0f;
			velocity.y = 0.0f;
		}
	}

	if (transform->position.x - (renderer->width / 2.0f) <= -border) transform->position.x = -border + (renderer->width / 2.0f);
	else if (transform->position.x + (renderer->width / 2.0f) >= border) transform->position.x = border - (renderer->width / 2.0f);

	if (transform->position.y + (renderer->width / 2.0f) >= border) transform->position.y = border - (renderer->width / 2.0f);
	else if (transform->position.y - (renderer->width / 2.0f) <= -border) transform->position.y = -border + (renderer->width / 2.0f);
}