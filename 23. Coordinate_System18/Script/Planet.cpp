#include <Planet.h>
#include "Object.h"
#include "InputManager.h"
#include "Material.h"
#include <gl/glm/glm.hpp>

void Planet::Start() {
	tr = gameObject->GetComponent<Transform>();
	mr = gameObject->GetComponent<MeshRenderer3D>();
	if (centerAnchor != nullptr) centerAnchorTr = centerAnchor->GetComponent<Transform>();
}

void Planet::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (centerAnchorTr != nullptr)
		tr->SetLocalPosition(centerAnchorTr->worldPosition.x, centerAnchorTr->worldPosition.y, centerAnchorTr->worldPosition.z);

	if (inputManager.GetKeyPressed(GLFW_KEY_LEFT_SHIFT) &&
		inputManager.GetKeyDown(GLFW_KEY_M)) {
		mr->isValid = false;
		mr->isWireframe = true;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_M)) {
		mr->isValid = true;
		mr->isWireframe = false;
	}

	if (isCenter) {
		if (inputManager.GetKeyDown(GLFW_KEY_2)) {
			isScaling = !isScaling;
		}

		if (isScaling) {
			if (isScaleUp) {
				scaleWeight += deltaTime;
				if (scaleWeight >= 1.0f) {
					scaleWeight = 1.0f;
					isScaleUp = false;
				}
			}
			else {
				scaleWeight -= deltaTime;
				if (scaleWeight <= 0.0f) {
					scaleWeight = 0.0f;
					isScaleUp = true;
				}
			}

			colorWeight += deltaTime;
			if (colorWeight >= 1.0f) {
				colorWeight = 0.0f;
				colorMode = (colorMode + 1) % 4;
			}
			if (colorMode == 0) {
				vec4 startColor = { 1.0f, 0.0f, 0.0f, 1.0f };
				vec4 endColor = { 0.5f, 0.0f, 1.0f, 1.0f };
				vec4 newColor = mix(startColor, endColor, colorWeight);
				mr->materials[0]->SetVec4("tColor", newColor);
			}
			else if (colorMode == 1) {
				vec4 startColor = { 0.5f, 0.0f, 1.0f, 1.0f };
				vec4 endColor = { 0.0f, 1.0f, 1.0f, 1.0f };
				vec4 newColor = mix(startColor, endColor, colorWeight);
				mr->materials[0]->SetVec4("tColor", newColor);
			}
			else if (colorMode == 2) {
				vec4 startColor = { 0.0f, 1.0f, 1.0f, 1.0f };
				vec4 endColor = { 0.5f, 1.0f, 0.0f, 1.0f };
				vec4 newColor = mix(startColor, endColor, colorWeight);
				mr->materials[0]->SetVec4("tColor", newColor);
			}
			else if (colorMode == 3) {
				vec4 startColor = { 0.5f, 1.0f, 0.0f, 1.0f };
				vec4 endColor = { 1.0f, 0.0f, 0.0f, 1.0f };
				vec4 newColor = mix(startColor, endColor, colorWeight);
				mr->materials[0]->SetVec4("tColor", newColor);
			}
		}

		vec3 startScale = { 1.0f, 1.0f, 1.0f };
		vec3 endScale = { 2.0f, 2.0f, 2.0f };
		vec3 newScale = mix(startScale, endScale, scaleWeight);
		tr->SetLocalScale(newScale.x, newScale.y, newScale.z);
	}
}