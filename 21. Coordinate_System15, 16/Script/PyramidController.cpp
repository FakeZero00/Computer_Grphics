#include "PyramidController.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "InputManager.h"

extern map<string, GLuint> shaders;

void PyramidController::Start() {
	Material* localPosColorMat = new Material(shaders["LocalPosColor"]);

	for (int i = 0; i < 4; ++i) {
		Object* parentCenter = gameObject->Instantiate("ParentCenter_" + to_string(i));
		objects.push_back(parentCenter);
		Transform* parentCenterTr = parentCenter->GetComponent<Transform>();
		parentCenterTr->SetLocalRotation(0.0f, 90.0f * (float)i, 0.0f);

		Object* lineCenter = parentCenter->Instantiate("LineCenter_" + to_string(i));
		Transform* lineCenterTr = lineCenter->GetComponent<Transform>();
		lineCenterTr->SetLocalPosition(0.0f, 0.0f, 1.0f);
		lineCenterTr->SetLocalRotation(-63.5f, 0.0f, 180.0f);
		
		Object* polygon = lineCenter->Instantiate("Polygon_" + to_string(i));
		polygon->AddComponent<MeshRenderer3D>(meshes["Triangle"], localPosColorMat);
		Transform* polygonTr = polygon->GetComponent<Transform>();
		polygonTr->SetLocalPosition(0.0f, 0.0f, -2.236f);
		polygonTr->SetLocalRotation(-90.0f, 0.0f, 0.0f);
	}

	floorObject = gameObject->Instantiate("Floor");
	floorObject->AddComponent<MeshRenderer3D>(meshes["Plane"], localPosColorMat);
	objects.push_back(floorObject);
}

void PyramidController::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	
	if (inputManager.GetKeyDown(GLFW_KEY_6)) {
		is6Move = true;
		is7Move = false;
		is6Rotating = !is6Rotating;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_7)) {
		is6Move = false;
		is7Move = true;
		is7Rotating = !is7Rotating;
	}

	if (is6Rotating) {
		weight6 += deltaTime * 0.5f;
		if (weight6 >= 1.0f) weight6 = 1.0f;
	}
	else {
		weight6 -= deltaTime * 0.5f;
		if (weight6 < 0.0f) weight6 = 0.0f;
	}

	if (is6Move) {
		quat startRotation = quat(vec3(radians(-63.5f), 0.0f, radians(180.0f)));

		for (int i = 0; i < 4; ++i) {
			Transform* parentTr = objects[i]->GetComponent<Transform>();
			Transform* childTr = parentTr->children[0]; // LineCenter

			//0도부터 -233도까지, 원하는 각도 자체를 weight6에 따라 직접 보간
			float currentAngle = glm::mix(0.0f, glm::radians(-233.0f), weight6);

			//보간된 각도로 매 프레임 현재의 delta 회전값을 생성
			quat currentDeltaRotation = quat(vec3(currentAngle, 0.0f, 0.0f));

			//시작 회전값에 현재의 델타 회전값을 곱해 로컬 기준(start * delta)으로 적용
			childTr->rotation = normalize(startRotation * currentDeltaRotation);
			childTr->CalculateWorldMatrix();
		}
	}

	if (is7Rotating) {
		if (weight7[0] < 1.0f) {
			weight7[0] += deltaTime * 0.5f;
			if (weight7[0] > 1.0f) weight7[0] = 1.0f;
		}
		else if (weight7[1] < 1.0f) {
			weight7[1] += deltaTime * 0.5f;
			if (weight7[1] > 1.0f) weight7[1] = 1.0f;
		}
		else if (weight7[2] < 1.0f) {
			weight7[2] += deltaTime * 0.5f;
			if (weight7[2] > 1.0f) weight7[2] = 1.0f;
		}
		else if (weight7[3] < 1.0f) {
			weight7[3] += deltaTime * 0.5f;
			if (weight7[3] > 1.0f) weight7[3] = 1.0f;
		}
	}
	else {
		if (weight7[0] > 0.0f) {
			weight7[0] -= deltaTime * 1.0f;
			if (weight7[0] < 0.0f) weight7[0] = 0.0f;
		}
		else if (weight7[1] > 0.0f) {
			weight7[1] -= deltaTime * 1.0f;
			if (weight7[1] < 0.0f) weight7[1] = 0.0f;
		}
		else if (weight7[2] > 0.0f) {
			weight7[2] -= deltaTime * 1.0f;
			if (weight7[2] < 0.0f) weight7[2] = 0.0f;
		}
		else if (weight7[3] > 0.0f) {
			weight7[3] -= deltaTime * 1.0f;
			if (weight7[3] < 0.0f) weight7[3] = 0.0f;
		}
	}

	if (is7Move) {
		quat startRotation = quat(vec3(radians(-63.5f), 0.0f, radians(180.0f)));
		quat deltaRotation = quat(vec3(radians(-116.5f), 0.0f, 0.0f));
		quat endRotation = normalize(startRotation * deltaRotation);

		for (int i = 0; i < 4; ++i) {
			Transform* parentTr = objects[i]->GetComponent<Transform>();
			Transform* childTr = parentTr->children[0]; // LineCenter

			//0도부터 -233도까지, 원하는 각도 자체를 weight6에 따라 직접 보간
			float currentAngle = glm::mix(0.0f, glm::radians(-116.5f), weight7[i]);

			//보간된 각도로 매 프레임 현재의 delta 회전값을 생성
			quat currentDeltaRotation = quat(vec3(currentAngle, 0.0f, 0.0f));

			//시작 회전값에 현재의 델타 회전값을 곱해 로컬 기준(start * delta)으로 적용
			childTr->rotation = normalize(startRotation * currentDeltaRotation);
			childTr->CalculateWorldMatrix();
		}
	}
}