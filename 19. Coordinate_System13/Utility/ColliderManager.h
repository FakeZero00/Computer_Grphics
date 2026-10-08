#pragma once
#include "AppContext.h"
#include "Collider.h"
#include "BoxCollider.h"

class ColliderManager {
public:
	ColliderManager(AppContext& ctx);

	bool CheckCollision(Collider* colA, Collider* colB);

	bool CheckBoxBox(BoxCollider* colA, BoxCollider* colB);

	void Update();

private:
	AppContext& ctx;
};