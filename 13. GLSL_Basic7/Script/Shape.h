#pragma once
#include "Component.h"

class Shape : public Component{
public:
	bool isSelected = false;
	float moveSpeed = 1.0f;

	void Select();
	void Deselect();

	void Update(float deltaTime) override;
};