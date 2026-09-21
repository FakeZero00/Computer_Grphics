#pragma once
#include "Component.h"
#include <vector>
using namespace std;

class EraserManager : public Component {
public:
	Object* eraserObject = nullptr;
	vector<Object*> squares;

	EraserManager(Object* obj) : eraserObject(obj) {}

	void CreateSquares();

	void Start() override;
	void Update(float deltaTime) override;
};