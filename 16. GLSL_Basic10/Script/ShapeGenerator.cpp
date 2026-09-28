#include "ShapeGenerator.h"
#include "InputManager.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "BoxCollider.h"
#include "Spline.h"
#include "Object.h"
using namespace std;

#include "ShapeMovement.h"

extern map<string, GLuint> shaders;

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	
	if (inputManager.GetKeyDown(GLFW_MOUSE_BUTTON_LEFT)) {
		vec4 color{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f };
		float scale = urdScale(dre);

		Object* newObj = gameObject->Instantiate("isoPolygon_Mesh");
		Transform* objTr = newObj->GetComponent<Transform>();
		objTr->SetLocalPosition(inputManager.GetMouseX(), inputManager.GetMouseY(), 0.0f);
		objTr->SetLocalScale(scale, scale, 0.0f);

		MeshRenderer3D* objMr = newObj->AddComponent<MeshRenderer3D>(isoPolyMesh, new Material{ shaders["Standard"] });
		objMr->materials[0]->SetVec4("tColor", color);

		BoxCollider* col = newObj->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f });
		col->isDebug = true;
		newObj->AddComponent<ShapeMovement>();

		generatedObjects.push_back(newObj);
	}
}