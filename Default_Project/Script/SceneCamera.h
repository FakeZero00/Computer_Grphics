#pragma once
#include "Component.h"

class SceneCamera : public Component {
public:
	SceneCamera(float rotX, float rotY);

	float walkSpeed = 5.0f;
	float dashSpeed = 15.0f;
	float sensitivity = 100.0f;

	float lastMouseX = 0.0f;
	float lastMouseY = 0.0f;

	float yaw;
	float pitch;

	void Update(float deltaTime) override;
};