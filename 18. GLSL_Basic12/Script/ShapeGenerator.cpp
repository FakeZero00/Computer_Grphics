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

#include "Major.h"

extern map<string, GLuint> shaders;

Object* ShapeGenerator::createShape(string name, int x, int y) {
	Object* obj = gameObject->Instantiate(name);
	MeshRenderer3D* mr;
	Transform* tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(-1.0f + (x * 2.0f / (float)vertical) + centerOffsetX, 1.0f - (y * 2.0f / (float)horizontal) - centerOffsetY, 0.0f);
	
	if (name == "regularPolygon") {
		mr = obj->AddComponent<MeshRenderer3D>(regularPolyMesh, new Material{ shaders["Standard"] });
		mr->materials[0]->SetVec4("tColor", vec4{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f });
		float scale = urdScale(dre) * 10.0f / std::max((float)vertical, (float)horizontal);
		tr->SetLocalScale( scale, scale, 1.0f);
	}
	else if (name == "arcRegularPolygon") {
		mr = obj->AddComponent<MeshRenderer3D>(regularPolyMesh, new Material{ shaders["Standard"] });
		mr->materials[0]->SetVec4("tColor", vec4{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f });
		float scale = urdScale(dre) * 10.0f /std::max((float)vertical, (float)horizontal);
		tr->SetLocalScale(scale, scale, 1.0f);
		tr->SetLocalRotation(0.0f, 0.0f, 180.0f);
	}
	else if (name == "rect") {
		mr = obj->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
		mr->materials[0]->SetVec4("tColor", vec4{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f });
		float scale = urdScaleRect(dre) * 10.0f / std::max((float)vertical, (float)horizontal);
		tr->SetLocalScale(scale, scale, 1.0f);
	}
	
	BoxCollider* col = obj->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f });
	return obj;
}

void ShapeGenerator::Start() {
	cout << "ShapeGenerator Started" << endl;

	
}

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	
	
}