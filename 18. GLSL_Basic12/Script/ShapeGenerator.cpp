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

void ShapeGenerator::Move(int x, int y) {
	majorPos[0] = x;
	majorPos[1] = y;

	Transform* tr = major->GetComponent<Transform>();
	tr->SetLocalPosition(-1.0f + (x * 2.0f / (float)vertical) + centerOffsetX, 1.0f - (y * 2.0f / (float)horizontal) - centerOffsetY, 0.0f);
}

void ShapeGenerator::Start() {
	cout << "ShapeGenerator Started" << endl;

	centerOffsetX = 1.0f / (float)vertical;
	centerOffsetY = 1.0f / (float)horizontal;

	finalPos[0] = horizontal % 2 == 0 ? 0 : vertical - 1;
	finalPos[1] = horizontal - 1;
	cout << "Final Position: (" << finalPos[0] << ", " << finalPos[1] << ")" << endl;

	for (int i = 0; i < horizontal; i++) {
		board.push_back({});
		for (int j = 0; j < vertical; j++) {
			board[i].push_back(NULL);
		}
	}

	for (int i = 0; i < horizontal; i++) {
		for (int j = 0; j < vertical; j++) {
			if (i == 0 && j == 0) continue;
			float rand = urdColor(dre);
			if (rand < 0.11f) board[i][j] = createShape("regularPolygon", j, i);
			else if (rand < 0.22f) board[i][j] = createShape("arcRegularPolygon", j, i);
			else if (rand < 0.33f) board[i][j] = createShape("rect", j, i);
		}
	}

	major = createShape("rect", 0, 0);
	major->AddComponent<Major>();
}

void ShapeGenerator::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	
	if (inputManager.GetKeyDown(GLFW_KEY_SPACE)) {
		isStart = !isStart;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_KP_ADD)) {
		if(defaultCooltime > 0.2f) defaultCooltime -= 0.1f;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_KP_SUBTRACT)) {
		if (defaultCooltime < 1.0f) defaultCooltime += 0.1f;
	}

	if (isStart) {
		if (cooltime > 0.0f) cooltime -= deltaTime;
		else {
			Move(majorPos[0] + direction[0], majorPos[1] + direction[1]);
			cooltime = defaultCooltime;
			if (isDown) {
				isDown = false;
				direction[0] = -currentDirX;
				direction[1] = 0;
			}
			else if (majorPos[0] == finalPos[0] && majorPos[1] == finalPos[1]) {
				isStart = false;
			}
			else if (majorPos[0] == horizontal - 1 || majorPos[0] == 0){
				currentDirX = direction[0];
				direction[0] = 0;
				direction[1] = 1;
				isDown = true;
			}
		}
	}
}