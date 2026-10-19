#include "Camera.h"
#include "Object.h"
#include "Transform.h"
#include "ScreenSize.h"
#include <gl/glm/gtc/matrix_transform.hpp>

extern ScreenSize screenSize;

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

	vec3 eye = tr->worldPosition;

	//월드 회전이 적용된 forward와 up 벡터를 계산
	mat3 worldRot = mat3(tr->worldMatrix);
	vec3 worldForward = glm::normalize(worldRot * vec3(0.0f, 0.0f, 1.0f));
	vec3 worldUp = glm::normalize(worldRot * vec3(0.0f, 1.0f, 0.0f));

	return lookAt(eye, eye + worldForward, worldUp);
}

mat4 Camera::GetProjectionMatrix() {
	if (isOrthographic) {
		float halfWidth = width / 2.0f / 100.0f;
		float halfHeight = height / 2.0f / 100.0f;
		return ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
	}
	else return perspective(radians(fov), aspectRatio, nearPlane, farPlane);
}

Component* Camera::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	int width = props.contains("width") ? static_cast<int>(props["width"]) : screenSize.width;
	int height = props.contains("height") ? static_cast<int>(props["height"]) : screenSize.height;

	Camera* cam = obj->AddComponent<Camera>(width, height);
	if (props.contains("fov")) cam->fov = props["fov"];
	if (props.contains("nearPlane")) cam->nearPlane = props["nearPlane"];
	if (props.contains("farPlane")) cam->farPlane = props["farPlane"];
	return cam;
}

REGISTER_COMPONENT(Camera)