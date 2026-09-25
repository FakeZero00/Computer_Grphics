#pragma once
#include "../Common.h"

class Scene {
public:
	string name;

	Object* Instantiate(AppContext& ctx, string objName);
	Object* FindObject(AppContext& ctx, string objName);

	virtual void LoadScene(AppContext& ctx) {}
};