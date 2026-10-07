#pragma once
#include "Component.h"
#include <gl/glm/glm.hpp>
using namespace glm;

class Camera : public Component {
public:
	static Camera* mainCamera;

	float fov = 60.0f;
	float aspectRatio = 1600.0f / 900.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	Camera(float width, float height);
	~Camera();

	mat4 GetViewMatrix();
	mat4 GetProjectionMatrix();
};