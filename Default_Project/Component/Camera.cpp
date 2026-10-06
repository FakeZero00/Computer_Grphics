#include "Camera.h"
#include "Object.h"
#include "Transform.h"
#include <gl/glm/gtc/matrix_transform.hpp>

Camera* Camera::mainCamera = nullptr;

Camera::Camera() {
	if (mainCamera == nullptr) {
		mainCamera = this;
	}

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
	return perspective(radians(fov), aspectRatio, nearPlane, farPlane);
}