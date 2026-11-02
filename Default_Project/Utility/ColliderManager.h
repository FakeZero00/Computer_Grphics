#pragma once
#include "AppContext.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

class ColliderManager {
public:
	ColliderManager(AppContext& ctx);

	bool CheckCollision(Collider* colA, Collider* colB);

	bool CheckBoxBox(BoxCollider* colA, BoxCollider* colB);
	bool CheckSphereSphere(SphereCollider* colA, SphereCollider* colB);
	bool CheckBoxSphere(BoxCollider* box, SphereCollider* sphere);

	void Update();

private:
	AppContext& ctx;
};