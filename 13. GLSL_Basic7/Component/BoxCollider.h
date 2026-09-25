#pragma once
#include "Collider.h"
#include <gl/glm/glm.hpp>
using namespace glm;

class BoxCollider : public Collider {
public:
	vec3 center;
	vec3 size;

	vec3 minPos;
	vec3 maxPos;

	bool isDebug = false;

	BoxCollider(vec3 center = vec3{ 0.0 }, vec3 size = vec3{ 1.0 });

	void RecalculateCollision() override;
	void Start() override;
	void Render() override;

private:
	void InitDebugRender() override;
};