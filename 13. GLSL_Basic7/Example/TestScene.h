#pragma once
#include "Scene.h"

class TestScene : public Scene {
public:
	TestScene();

	void LoadScene(AppContext& ctx, map<string, GLuint>& shaders) override;
};