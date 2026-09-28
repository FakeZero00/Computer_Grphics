#include "ShapeGenerator.h"
#include "InputManager.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "BoxCollider.h"
#include "Spline.h"
#include <string>
#include <ranges>
using namespace std;

#include "ShapeMovement.h"

extern map<string, GLuint> shaders;

void ShapeGenerator::Start() {
	cout << "ShapeGenerator Started" << endl;
}

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	
}