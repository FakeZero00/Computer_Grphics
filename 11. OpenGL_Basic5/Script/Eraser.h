#pragma once
#include "Component.h"

class Eraser : public Component {
public:
	void OnTriggerEnter(Object* other) override;

	void Update(float deltaTime) override;
};