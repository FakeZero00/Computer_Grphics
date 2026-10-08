#include "ObjectManagement.h"
#include "Object.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "InputManager.h"

extern map<string, GLuint> shaders;

void ObjectManagement::Start() {
	//마테리얼 생성
	Material* redMat = new Material(shaders["Standard"]);
	redMat->SetVec4("tColor", vec4(1.0f, 0.0f, 0.0f, 1.0f));

	Material* greenMat = new Material(shaders["Standard"]);
	greenMat->SetVec4("tColor", vec4(0.0f, 1.0f, 0.0f, 1.0f));

	Material* blueMat = new Material(shaders["Standard"]);
	blueMat->SetVec4("tColor", vec4(0.0f, 0.0f, 1.0f, 1.0f));

	Material* magentaMat = new Material(shaders["Standard"]);
	magentaMat->SetVec4("tColor", vec4(1.0f, 0.0f, 1.0f, 1.0f));

	Material* yellowMat = new Material(shaders["Standard"]);
	yellowMat->SetVec4("tColor", vec4(1.0f, 1.0f, 0.0f, 1.0f));

	Material* cyanMat = new Material(shaders["Standard"]);
	cyanMat->SetVec4("tColor", vec4(0.0f, 1.0f, 1.0f, 1.0f));

	//Object 생성 및 초기화
	for (size_t i = 0; i < meshes.size(); ++i) {
		Object* obj = gameObject->Instantiate("obj");
		objects.push_back(obj);
	}

	objects[0]->AddComponent<MeshRenderer3D>(meshes[0], redMat);
	objects[1]->AddComponent<MeshRenderer3D>(meshes[1], greenMat);
	objects[2]->AddComponent<MeshRenderer3D>(meshes[2], blueMat);
	objects[3]->AddComponent<MeshRenderer3D>(meshes[3], magentaMat);
	objects[4]->AddComponent<MeshRenderer3D>(meshes[4], yellowMat);
	objects[5]->AddComponent<MeshRenderer3D>(meshes[5], cyanMat);
	objects[6]->AddComponent<MeshRenderer3D>(meshes[6], redMat);
	objects[7]->AddComponent<MeshRenderer3D>(meshes[7], greenMat);
	objects[8]->AddComponent<MeshRenderer3D>(meshes[8], blueMat);
	objects[9]->AddComponent<MeshRenderer3D>(meshes[9], magentaMat);

	for (auto& obj : objects) {
		obj->isValid = false;
	}
}

void ObjectManagement::AllDisable() {
	for (auto& obj : objects) {
		obj->isValid = false;
	}
}

void ObjectManagement::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;

	if (inputManager.GetKeyDown(GLFW_KEY_1)) {
		objects[0]->isValid = !objects[0]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_2)) {
		objects[1]->isValid = !objects[1]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_3)) {
		objects[2]->isValid = !objects[2]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_4)) {
		objects[3]->isValid = !objects[3]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_5)) {
		objects[4]->isValid = !objects[4]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_6)) {
		objects[5]->isValid = !objects[5]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_7)) {
		objects[6]->isValid = !objects[6]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_8)) {
		objects[7]->isValid = !objects[7]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_9)) {
		objects[8]->isValid = !objects[8]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_0)) {
		objects[9]->isValid = !objects[9]->isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		AllDisable();
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_C)) {
		AllDisable();
		int rand1 = randCube(dre);
		int rand2 = randCube(dre);
		while (rand1 == rand2) {
			rand2 = randCube(dre);
		}
		objects[rand1]->isValid = true;
		objects[rand2]->isValid = true;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_T)) {
		AllDisable();
		int rand = randTri(dre);
		objects[rand]->isValid = true;
		objects[4]->isValid = true;
	}
}