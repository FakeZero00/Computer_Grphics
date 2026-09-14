#pragma once
#include "Component.h"
#include "InputManager.h"
#include "AppContext.h"
#include "BoxCollider2D.h"

class childSquare : public Component {
public:
	childSquare(AppContext& context, InputManager& inputManager);

	void SetSelected();
	void Destroy();

	void Awake() override;
	void Update(float deltaTime) override;

private:
	AppContext& context;
	InputManager& inputManager;
	BoxCollider2D* boxCollider = nullptr;

	bool isSelected = false;
};