#include "ShapeGenerator.h"
#include "InputManager.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"

extern map<string, GLuint> shaders;

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (generatedObjects.size() < 50) {
		if (inputManager.GetKeyDown(GLFW_KEY_P)) {
			Object* newObject = gameObject->Instantiate("Point");
			MeshRenderer3D* mr = newObject->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
			mr->material->SetVec4("tColor", vec4(urdColor(dre), urdColor(dre), urdColor(dre), 1.0f));
			Transform* tr = newObject->GetComponent<Transform>();
			tr->SetLocalPosition(urd(dre), urd(dre), urd(dre));
			tr->SetLocalScale(0.1f, 0.1f, 0.1f);

			generatedObjects.push_back(newObject);
		}
	}
}