#pragma once
#include "Component.h"
#include "Transform.h"
#include "Position2D.h"

class BoxCollider2D : public Component {
public:
	BoxCollider2D(float width, float height);

	bool Contains(float x, float y);

	void Awake() override;

private:
	Transform* transform = nullptr;

	Position2D minPos;
	Position2D maxPos;

	float width;
	float height;
};