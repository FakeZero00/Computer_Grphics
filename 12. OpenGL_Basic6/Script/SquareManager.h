#pragma once
#include "Component.h"

class SquareManager : public Component {
public:
	void Start() override;
	void Update(float deltaTime) override;
};