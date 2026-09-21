#pragma once
#include "AppContext.h"
#include "BoxCollider2D.h"

class ColliderManager {
public:
	ColliderManager(AppContext& ctx);

	bool CheckCollision(BoxCollider2D* colA, BoxCollider2D* colB);
	void Update();

private:
	AppContext& ctx;
};