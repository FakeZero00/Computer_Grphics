#pragma once
#include "Component.h"
#include "MeshRenderer2D.h"

class SquareSpawner : public Component {
public:
	void Execute();
	Object* SpawnParticle(MeshRenderer2D* renderer, float offsetX, float offsetY, float count, float vx, float vy, bool outline = false);
};