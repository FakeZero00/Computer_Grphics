#include "ShapeGenerator.h"
#include "InputManager.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "BoxCollider.h"
#include "Spline.h"
#include <string>
using namespace std;

#include "ShapeMovement.h"

extern map<string, GLuint> shaders;

Object* ShapeGenerator::createShape(string name) {
	Object* newObj = gameObject->Instantiate(name);
	MeshRenderer3D* newMr;
	BoxCollider* newCol;
	if (name == "regularPolygon") {
		newMr = newObj->AddComponent<MeshRenderer3D>(regularPolyMesh, new Material{ shaders["Standard"] });
		newMr->materials[0]->SetVec4("tColor", vec4{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f });
		Transform* tr = newObj->GetComponent<Transform>();
		tr->SetLocalScale(3.0f, 3.0f, 1.0f);
	}
	else if (name == "rightPolygon") {
		newMr = newObj->AddComponent<MeshRenderer3D>(rightPolyMesh, new Material{ shaders["Standard"] });
		newMr->materials[0]->SetVec4("tColor", vec4{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f });
		Transform* tr = newObj->GetComponent<Transform>();
		tr->SetLocalScale(0.5f, 0.5f, 1.0f);
	}
	else if (name == "rectangle") {
		newMr = newObj->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
		newMr->materials[0]->SetVec4("tColor", vec4{ urdColor(dre), urdColor(dre), urdColor(dre), 1.0f});
		Transform* tr = newObj->GetComponent<Transform>();
		tr->SetLocalScale(0.5f, 0.5f, 1.0f);
	}
	else if (name == "regularPolygonCol") {
		newMr = newObj->AddComponent<MeshRenderer3D>(regularPolyMesh, new Material{ shaders["Standard"] });
		newMr->materials[0]->SetVec4("tColor", vec4{ 0.2f, 0.2f, 0.2f, 1.0f });
		newObj->AddComponent<Spline>(regularPolyCP, vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		Transform* tr = newObj->GetComponent<Transform>();
		tr->SetLocalScale(3.0f, 3.0f, 1.0f);
	}
	else if (name == "rightPolygonCol") {
		newMr = newObj->AddComponent<MeshRenderer3D>(rightPolyMesh, new Material{ shaders["Standard"] });
		newMr->materials[0]->SetVec4("tColor", vec4{ 0.2f, 0.2f, 0.2f, 1.0f });
		newObj->AddComponent<Spline>(rightPolyCP, vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		Transform* tr = newObj->GetComponent<Transform>();
		tr->SetLocalScale(0.5f, 0.5f, 1.0f);
	}
	else if (name == "rectangleCol") {
		newMr = newObj->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
		newMr->materials[0]->SetVec4("tColor", vec4{ 0.2f, 0.2f, 0.2f, 1.0f });
		newObj->AddComponent<Spline>(rectCP, vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		Transform* tr = newObj->GetComponent<Transform>();
		tr->SetLocalScale(0.5f, 0.5f, 1.0f);
	}

	newCol = newObj->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f });
	if (name == "regularPolygonCol" || name == "rightPolygonCol" || name == "rectangleCol") {
		newCol->isDebug = false;
	}

	generatedObjects.push_back(newObj);
	return newObj;
}

void ShapeGenerator::Start() {
	cout << "ShapeGenerator Started" << endl;

	Object* obj;
	Transform* tr;
	MeshRenderer3D* mr;
	BoxCollider* col;
	//도형 1
	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.7f, 0.9f, 0.0f);

	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.76f, 0.9f, 0.0f);

	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.7f, 0.8f, 0.0f);

	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.76f, 0.8f, 0.0f);

	//도형 2
	obj = createShape("regularPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalRotation(0.0f, 0.0f, 180.0f);
	tr->SetLocalPosition(0.76f, 0.6f, 0.0f);

	obj = createShape("regularPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalRotation(0.0f, 0.0f, 90.0f);
	tr->SetLocalPosition(0.85f, 0.5f, 0.0f);

	obj = createShape("regularPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalRotation(0.0f, 0.0f, -90.0f);
	tr->SetLocalPosition(0.67f, 0.5f, 0.0f);

	obj = createShape("regularPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.76f, 0.4f, 0.0f);

	//도형 3
	obj = createShape("rightPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.73f, 0.1f, 0.0f);

	obj = createShape("rightPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalRotation(0.0f, 0.0f, 180.0f);
	tr->SetLocalPosition(0.78f, 0.2f, 0.0f);

	//도형 4
	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.76f, -0.2f, 0.0f);

	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.7f, -0.3f, 0.0f);

	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.76f, -0.3f, 0.0f);

	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.82f, -0.3f, 0.0f);

	obj = createShape("rectangleCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.76f, -0.4f, 0.0f);

	//도형 5
	obj = createShape("regularPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.72f, -0.7f, 0.0f);

	obj = createShape("regularPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalRotation(0.0f, 0.0f, 180.0f);
	tr->SetLocalPosition(0.77f, -0.66f, 0.0f);

	obj = createShape("regularPolygonCol");
	tr = obj->GetComponent<Transform>();
	tr->SetLocalPosition(0.82f, -0.7f, 0.0f);

	//정삼각형 생성
	for (int i = 0; i < 7; i++) {
		obj = createShape("regularPolygon");
		tr = obj->GetComponent<Transform>();
		tr->SetLocalPosition(urdPos(dre), urdPos2(dre), 0.0f);
	}

	//직각삼각형 생성
	for (int i = 0; i < 2; i++) {
		obj = createShape("rightPolygon");
		tr = obj->GetComponent<Transform>();
		tr->SetLocalPosition(urdPos(dre), urdPos2(dre), 0.0f);
	}

	//사각형 생성
	for (int i = 0; i < 9; i++){
		obj = createShape("rectangle");
		tr = obj->GetComponent<Transform>();
		tr->SetLocalPosition(urdPos(dre), urdPos2(dre), 0.0f);
	}
}

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
}