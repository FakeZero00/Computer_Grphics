#include "PyramidController.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "InputManager.h"

extern map<string, GLuint> shaders;

void PyramidController::ResetObjects() {
	for (int i = 0; i < 4; ++i) {
		Transform* parentTr = objects[i]->GetComponent<Transform>();
		Transform* childTr = parentTr->children[0]; // LineCenter
		Transform* polygonTr = childTr->children[0]; // Polygon

		polygonTr->SetLocalPosition(0.0f, 0.0f, -2.236f);
		polygonTr->SetLocalRotation(-90.0f, 0.0f, 0.0f);

		childTr->SetLocalPosition(0.0f, 0.0f, 1.0f);
		childTr->SetLocalRotation(-63.5f, 0.0f, 180.0f);

		parentTr->SetLocalRotation(0.0f, 90.0f * (float)i, 0.0f);

		polygonTr->gameObject->isValid = false;
	}
	floorObject->isValid = false;

	is6Move = false;
	is6Rotating = false;
	weight6 = 0.0f;

	is7Move = false;
	is7Rotating = false;
	weight7[0] = 0.0f;
	weight7[1] = 0.0f;
	weight7[2] = 0.0f;
	weight7[3] = 0.0f;

	is8Rotating = false;
	rotateIndex[0] = 0;
	rotateIndex[1] = 0;
	totalRotation = 0.0f;

	is9Rotating = false;
	weight9 = 0.0f;

	isValid = false;
}

void PyramidController::Start() {
	Material* localPosColorMat = new Material(shaders["LocalPosColor"]);
	Material* redMat = new Material(shaders["Standard"]);
	redMat->SetVec4("tColor", vec4(1.0f, 0.0f, 0.0f, 1.0f));

	Material* greenMat = new Material(shaders["Standard"]);
	greenMat->SetVec4("tColor", vec4(0.0f, 1.0f, 0.0f, 1.0f));

	Material* blueMat = new Material(shaders["Standard"]);
	blueMat->SetVec4("tColor", vec4(0.0f, 0.0f, 1.0f, 1.0f));

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
		if (i == 0) polygon->AddComponent<MeshRenderer3D>(meshes["Triangle"], redMat);
		else if (i == 1) polygon->AddComponent<MeshRenderer3D>(meshes["Triangle"], greenMat);
		else if (i == 2) polygon->AddComponent<MeshRenderer3D>(meshes["Triangle"], blueMat);
		else polygon->AddComponent<MeshRenderer3D>(meshes["Triangle"], localPosColorMat);
		Transform* polygonTr = polygon->GetComponent<Transform>();
		polygonTr->SetLocalPosition(0.0f, 0.0f, -2.236f);
		polygonTr->SetLocalRotation(-90.0f, 0.0f, 0.0f);
	}

	floorObject = gameObject->Instantiate("Floor");
	floorObject->AddComponent<MeshRenderer3D>(meshes["Plane"], localPosColorMat);
	objects.push_back(floorObject);

	for (int i = 0; i < 4; ++i) {
		Transform* parentTr = objects[i]->GetComponent<Transform>();
		Transform* childTr = parentTr->children[0]; // LineCenter
		Transform* polygonTr = childTr->children[0]; // Polygon

		polygonTr->gameObject->isValid = false;
	}
	floorObject->isValid = false;
}

void PyramidController::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	
	if (inputManager.GetKeyDown(GLFW_KEY_P)) {
		for (int i = 0; i < 4; ++i) {
			Transform* parentTr = objects[i]->GetComponent<Transform>();
			Transform* childTr = parentTr->children[0]; // LineCenter
			Transform* polygonTr = childTr->children[0]; // Polygon

			polygonTr->gameObject->isValid = !polygonTr->gameObject->isValid;
		}
		floorObject->isValid = !floorObject->isValid;
		isValid = !isValid;
	}
	else if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		ResetObjects();
	}

	if (isValid) {
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
		else if (inputManager.GetKeyDown(GLFW_KEY_8)) {
			if (!is8Rotating) {
				vector<int> indices = { 0, 1, 2, 3 };
				rotateIndex[0] = rand8(dre);
				rotateIndex[1] = (rotateIndex[0] + 2) % 4;
				is8Rotating = true;
				totalRotation = 0.0f;
			}
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_9)) {
			is9Rotating = !is9Rotating;
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

		if (is8Rotating) {
			float deltaAngle = deltaTime * 90.0f;
			totalRotation += deltaAngle;

			if (totalRotation >= 180.0f) {
				deltaAngle = 180.0f - (totalRotation - deltaAngle);
				totalRotation = 180.0f;
			}

			Transform* parentTr1 = objects[rotateIndex[0]]->GetComponent<Transform>();
			Transform* parentTr2 = objects[rotateIndex[1]]->GetComponent<Transform>();

			parentTr1->Rotate(0.0f, deltaAngle, 0.0f, true);
			parentTr2->Rotate(0.0f, deltaAngle, 0.0f, true);

			if (totalRotation >= 180.0f) is8Rotating = false;
		}

		if (is9Rotating) {
			weight9 += deltaTime * 0.5f;
			if (weight9 >= 1.0f) weight9 = 1.0f;
		}
		else {
			weight9 -= deltaTime * 0.5f;
			if (weight9 < 0.0f) weight9 = 0.0f;
		}

		quat startRotation = quat(vec3(radians(-90.0f), 0.0f, radians(0.0f)));

		for (int i = 0; i < 4; ++i) {
			Transform* parentTr = objects[i]->GetComponent<Transform>();
			Transform* childTr = parentTr->children[0]; // LineCenter
			Transform* polygonTr = childTr->children[0]; // Polygon

			//원하는 각도 자체를 weight9에 따라 직접 보간
			float currentAngle = glm::mix(0.0f, glm::radians(63.5f), weight9);

			//보간된 각도로 매 프레임 현재의 delta 회전값을 생성
			quat currentDeltaRotation = quat(vec3(currentAngle, 0.0f, 0.0f));

			//시작 회전값에 현재의 델타 회전값을 곱해 로컬 기준(start * delta)으로 적용
			polygonTr->rotation = normalize(startRotation * currentDeltaRotation);
			polygonTr->CalculateWorldMatrix();
		}
	}
}