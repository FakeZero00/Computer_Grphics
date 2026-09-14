#pragma once
#include "Component.h"
#include "InputManager.h"
#include <random>
#include <iostream>

class Director : public Component {
public:
	Director(InputManager& inputMgr);

	void Update(float deltaTime) override;

private:
	InputManager& inputManager;

	Object* Square1;
	Object* Square2;
	Object* Square3;
	Object* Square4;

	int counter1 = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;

	float size1 = 0.8f;
	float size2 = 0.8f;
	float size3 = 0.8f;
	float size4 = 0.8f;

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> urd{ 0.0f, 1.0f };
};