#include "Camera.h"
#include "Object.h"
#include "Transform.h"
#include <gl/glm/gtc/matrix_transform.hpp>

Camera* Camera::mainCamera = nullptr;

Camera::Camera(float width, float height) : width(width), height(height) {
	if (mainCamera == nullptr) {
		mainCamera = this;
	}

	aspectRatio = width / height;

	Expose("fov", &fov);
	Expose("aspectRatio", &aspectRatio);
	Expose("nearPlane", &nearPlane);
	Expose("farPlane", &farPlane);
}

Camera::~Camera() {
	if (mainCamera == this) {
		mainCamera = nullptr;
	}
}

mat4 Camera::GetViewMatrix() {
	Transform* tr = gameObject->GetComponent<Transform>();

	return lookAt(tr->worldPosition, tr->worldPosition + tr->forward, tr->up);
}

mat4 Camera::GetProjectionMatrix() {
	if (isOrthographic) {
		float halfWidth = width / 2.0f / 100.0f;
		float halfHeight = height / 2.0f / 100.0f;
		return ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
	}
	else return perspective(radians(fov), aspectRatio, nearPlane, farPlane);
}