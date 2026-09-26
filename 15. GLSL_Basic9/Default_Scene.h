#pragma once
#include "Scene.h"

class Default_Scene : public Scene {
public:
	Default_Scene();

	void LoadScene(AppContext& ctx) override;
};