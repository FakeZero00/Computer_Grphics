#pragma once
#include "Component.h"
#include "InputManager.h"
#include <iostream>

class InputTest : public Component {
public:
	InputTest(InputManager& inputMgr) : inputManager(inputMgr) {}

	void Update(float deltaTime) override {
		// 예시: 스페이스바가 눌렸는지 확인
		if (inputManager.GetKeyDown(GLFW_KEY_SPACE)) {
			// 스페이스바가 눌렸을 때의 동작
			std::cout << "Space key pressed!" << std::endl;
		}
	}

private:
	InputManager& inputManager;
};