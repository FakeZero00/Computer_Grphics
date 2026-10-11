#include "ObjectManagement.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"
#include "InputManager.h"
#include <gl/glm/glm.hpp>

extern map<string, GLuint> shaders;

void ObjectManagement::ResetObjects() {
	Transform* tr;

	if (scriptID == 0) {
		tr = gameObject->GetComponent<Transform>();
		tr->SetLocalPosition(0.0f, 0.0f, 0.0f);
		tr->SetLocalRotation(0.0f, 0.0f, 0.0f);
	}
	else if (scriptID == 1) {
		if (gameObject->name == "+X") {
			tr = gameObject->GetComponent<Transform>();
			tr->SetLocalRotation(0.0f, 0.0f, -90.0f);
		}
		else if (gameObject->name == "+Y") {
			tr = gameObject->GetComponent<Transform>();
			tr->SetLocalRotation(0.0f, 0.0f, 0.0f);
		}
		else if (gameObject->name == "+Z") {
			tr = gameObject->GetComponent<Transform>();
			tr->SetLocalRotation(90.0f, 0.0f, 0.0f);
		}
		else if (gameObject->name == "-X") {
			tr = gameObject->GetComponent<Transform>();
			tr->SetLocalRotation(0.0f, 0.0f, 90.0f);
		}
		else if (gameObject->name == "-Y") {
			tr = gameObject->GetComponent<Transform>();
			tr->SetLocalRotation(0.0f, 0.0f, 180.0f);
		}
		else if (gameObject->name == "-Z") {
			tr = gameObject->GetComponent<Transform>();
			tr->SetLocalRotation(-90.0f, 0.0f, 0.0f);
		}
	}
}

void ObjectManagement::Start() {
	//마테리얼 생성
	Material* localPosColorMat = new Material(shaders["LocalPosColor"]);
	
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

	string planeNames[6] = { "+X", "+Y", "+Z", "-X", "-Y", "-Z" };

	if (scriptID == 0) {
		Transform* tr;

		for (string name : planeNames) {
			objects[name] = gameObject->Instantiate(name);
			ObjectManagement* objM = objects[name]->AddComponent<ObjectManagement>(scriptID + 1, meshes);

			objM->objects[name] = objects[name]->Instantiate(name);
			objM->objects[name]->AddComponent<MeshRenderer3D>(meshes["Plane"], localPosColorMat);
			objM->objects[name]->AddComponent<ObjectManagement>(scriptID + 2, meshes);
			tr = objM->objects[name]->GetComponent<Transform>();
			tr->SetLocalPosition(0.0f, 1.0f, 0.0f);
		}

		//scriptID가 1인 오브젝트들의 초기화
		tr = objects["+X"]->GetComponent<Transform>();
		tr->SetLocalRotation(0.0f, 0.0f, -90.0f);

		tr = objects["+Y"]->GetComponent<Transform>();
		tr->SetLocalRotation(0.0f, 0.0f, 0.0f);

		tr = objects["+Z"]->GetComponent<Transform>();
		tr->SetLocalRotation(90.0f, 0.0f, 0.0f);

		tr = objects["-X"]->GetComponent<Transform>();
		tr->SetLocalRotation(0.0f, 0.0f, 90.0f);

		tr = objects["-Y"]->GetComponent<Transform>();
		tr->SetLocalRotation(0.0f, 0.0f, 180.0f);

		tr = objects["-Z"]->GetComponent<Transform>();
		tr->SetLocalRotation(-90.0f, 0.0f, 0.0f);
	}
}

void ObjectManagement::Update(float deltaTime) {
	InputManager inputManager = gameObject->ctx.inputManager;
	Transform* tr;

	if (inputManager.GetKeyDown(GLFW_KEY_R)) {
		ResetObjects();
	}

	if (scriptID == 0) {
		if (inputManager.GetKeyDown(GLFW_KEY_H)) {
			if (isDepthTestEnabled) {
				glDisable(GL_DEPTH_TEST);
				isDepthTestEnabled = false;
			}
			else {
				glEnable(GL_DEPTH_TEST);
				isDepthTestEnabled = true;
			}
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_Y)) {
			isYRotating = !isYRotating;
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_S)) {
			isXRotating = !isXRotating;
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_1)) {
			if (!is1Rotating) {
				vector<string> names = { "+X", "-X", "+Z", "-Z" };
				rotatingObjectName1[0] = names[rand1(dre)];

				names.erase(remove(names.begin(), names.end(), rotatingObjectName1[0]), names.end());
				string rmStr = ((rotatingObjectName1[0][0] == '+') ? "-" : "+") + rotatingObjectName1[0].substr(1);
				cout << "Removing: " << rmStr << endl;
				names.erase(remove(names.begin(), names.end(), rmStr), names.end());

				rotatingObjectName1[1] = names[rand1_2(dre)];

				is1Rotating = true;
				rotatingAngle1 = 0.0f;
			}
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_2)) {
			if (!is2Rotating) {
				vector<string> names = { "+X", "-X", "+Y", "-Y", "+Z", "-Z" };
				rotatingObjectName2[0] = names[rand2(dre)];

				names.erase(remove(names.begin(), names.end(), rotatingObjectName2[0]), names.end());
				string rmStr = ((rotatingObjectName2[0][0] == '+') ? "-" : "+") + rotatingObjectName2[0].substr(1);
				cout << "Removing: " << rmStr << endl;
				names.erase(remove(names.begin(), names.end(), rmStr), names.end());

				rotatingObjectName2[1] = names[rand2_2(dre)];

				startRot2[0] = objects[rotatingObjectName2[0]]->GetComponent<Transform>()->rotation;
				startRot2[1] = objects[rotatingObjectName2[1]]->GetComponent<Transform>()->rotation;

				endRot2[1] = objects[rotatingObjectName2[0]]->GetComponent<Transform>()->rotation;
				endRot2[0] = objects[rotatingObjectName2[1]]->GetComponent<Transform>()->rotation;

				//현재 두 부모 오브젝트가 향하는 실제 방향(월드의 Up축 기준)을 구합니다.
				vec3 dir0 = startRot2[0] * vec3(0.0f, 1.0f, 0.0f);
				vec3 dir1 = startRot2[1] * vec3(0.0f, 1.0f, 0.0f);

				//외적(Cross)으로 회전축을, 내적(Dot)으로 회전 각도를 구합니다.
				vec3 crossVec = glm::cross(dir0, dir1);
				float dotVal = glm::dot(dir0, dir1);

				glm::quat delta0to1;
				glm::quat delta1to0;

				//오차를 감안해 1.0이나 -1.0에 가까운지 검사합니다.
				if (dotVal < -0.999f) {
					// 180도 정반대 방향일 때 (예: +X와 -X가 자리를 바꿀 때)
					// 회전축이 소실되므로 임의의 직교 축을 하나 만들어 180도 회전시킵니다.
					vec3 up = abs(dir0.y) < 0.999f ? vec3(0.0f, 1.0f, 0.0f) : vec3(0.0f, 0.0f, 1.0f);
					vec3 axis = glm::normalize(glm::cross(dir0, up));

					delta0to1 = glm::angleAxis(glm::radians(180.0f), axis);
					delta1to0 = delta0to1; // 반대 방향 회전도 동일하게 180도
				}
				else if (dotVal > 0.999f) {
					// 0도 (이미 같은 방향을 보고 있을 때)
					delta0to1 = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // 회전 없음
					delta1to0 = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
				}
				else {
					// 90도 등 일반적인 각도로 꺾일 때
					vec3 axis = glm::normalize(crossVec); // 두 방향에 직교하는 순수 회전축
					float angle = glm::acos(dotVal);      // 두 방향 사이의 실제 각도(라디안)

					delta0to1 = glm::angleAxis(angle, axis);
					delta1to0 = glm::angleAxis(-angle, axis); // 반대로 갈 때는 각도만 마이너스(-)
				}

				//기존 회전 상태에 이 순수 회전량만 곱해서 목표 회전값 생성
				endRot2[0] = delta0to1 * startRot2[0];
				endRot2[1] = delta1to0 * startRot2[1];

				is2Rotating = true;
				rotatingAngle2 = 0.0f;
			}
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_4)) {
			is4Rotating = !is4Rotating;
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_5)) {
			is5Rotating = !is5Rotating;
		}

		if (isYRotating) {
			tr = gameObject->GetComponent<Transform>();
			tr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
		}

		if (isXRotating) {
			Transform* pXTr = objects["+X"]->GetComponent<Transform>();
			Transform* mXTr = objects["-X"]->GetComponent<Transform>();

			pXTr->Rotate(0.0f, 90.0f * deltaTime, 0.0f);
			mXTr->Rotate(0.0f, -90.0f * deltaTime, 0.0f);
		}

		if (is1Rotating) {
			float deltaAngle = 90.0f * deltaTime;
			rotatingAngle1 += deltaAngle;

			if (rotatingAngle1 >= 360.0f) {
				deltaAngle = 360.0f - (rotatingAngle1 - deltaAngle);
				rotatingAngle1 = 360.0f;
			}

			objects[rotatingObjectName1[0]]->GetComponent<Transform>()->Rotate(0.0f, deltaAngle, 0.0f, true);
			objects[rotatingObjectName1[1]]->GetComponent<Transform>()->Rotate(0.0f, deltaAngle, 0.0f, true);

			if (rotatingAngle1 >= 360.0f) is1Rotating = false;
		}

		if (is2Rotating) {
			float deltaAngle = 1.0f * deltaTime;
			rotatingAngle2 += deltaAngle;

			if (rotatingAngle2 >= 1.0f) {
				rotatingAngle2 = 1.0f;
			}

			objects[rotatingObjectName2[0]]->GetComponent<Transform>()->rotation = glm::slerp(startRot2[0], endRot2[0], rotatingAngle2);
			objects[rotatingObjectName2[0]]->GetComponent<Transform>()->CalculateWorldMatrix();
			objects[rotatingObjectName2[1]]->GetComponent<Transform>()->rotation = glm::slerp(startRot2[1], endRot2[1], rotatingAngle2);
			objects[rotatingObjectName2[1]]->GetComponent<Transform>()->CalculateWorldMatrix();

			if (rotatingAngle2 >= 1.0f) {
				is2Rotating = false;
				objects[rotatingObjectName2[0]]->GetComponent<ObjectManagement>()->objects[rotatingObjectName2[0]]->name = rotatingObjectName2[1];
				auto node = objects[rotatingObjectName2[0]]->GetComponent<ObjectManagement>()->objects.extract(rotatingObjectName2[0]);
				node.key() = rotatingObjectName2[1];
				objects[rotatingObjectName2[0]]->GetComponent<ObjectManagement>()->objects.insert(std::move(node));

				objects[rotatingObjectName2[1]]->GetComponent<ObjectManagement>()->objects[rotatingObjectName2[1]]->name = rotatingObjectName2[0];
				node = objects[rotatingObjectName2[1]]->GetComponent<ObjectManagement>()->objects.extract(rotatingObjectName2[1]);
				node.key() = rotatingObjectName2[0];
				objects[rotatingObjectName2[1]]->GetComponent<ObjectManagement>()->objects.insert(std::move(node));

				objects[rotatingObjectName2[0]]->name = rotatingObjectName2[1];
				objects[rotatingObjectName2[1]]->name = rotatingObjectName2[0];

				Object* temp = objects[rotatingObjectName2[0]];
				objects[rotatingObjectName2[0]] = objects[rotatingObjectName2[1]];
				objects[rotatingObjectName2[1]] = temp;
				
				cout << "Swapped: " << rotatingObjectName2[0] << " <-> " << rotatingObjectName2[1] << endl;
			}
		}

		if (is4Rotating) {
			objects["+X"]->GetComponent<Transform>()->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
			objects["-X"]->GetComponent<Transform>()->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
			objects["+Z"]->GetComponent<Transform>()->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
			objects["-Z"]->GetComponent<Transform>()->Rotate(0.0f, 90.0f * deltaTime, 0.0f, true);
		}

		if (is5Rotating) {
			objects["+Y"]->GetComponent<Transform>()->Rotate(90.0f * deltaTime, 0.0f, 0.0f, true);
			objects["-Y"]->GetComponent<Transform>()->Rotate(90.0f * deltaTime, 0.0f, 0.0f, true);
			objects["+Z"]->GetComponent<Transform>()->Rotate(90.0f * deltaTime, 0.0f, 0.0f, true);
			objects["-Z"]->GetComponent<Transform>()->Rotate(90.0f * deltaTime, 0.0f, 0.0f, true);
		}
	}
	else if (scriptID == 1) {
		if (inputManager.GetKeyDown(GLFW_KEY_T)) {
			isPYRotating = !isPYRotating;
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_F)) {
			if (objects.find("-Z") != objects.end()) {
				tr = objects["-Z"]->GetComponent<Transform>();
				tr->SetLocalPosition(0.0f, 1.0f, 0.0f);
				tr->SetLocalRotation(0.0f, 0.0f, 0.0f);
			}
			isMZRotating = !isMZRotating;
		}
		else if (inputManager.GetKeyDown(GLFW_KEY_B)) {
			isPZScaling = !isPZScaling;
		}

		if (isPYRotating) {
			if(objects.find("+Y") != objects.end()) {
				tr = objects["+Y"]->GetComponent<Transform>();
				tr->Rotate(0.0f, 0.0f, 90.0f * deltaTime);
			}
		}

		if (isMZRotating) {
			fWeight += deltaTime * 2.0f;
			if (fWeight > 1.0f) fWeight = 1.0f;
		}
		else {
			fWeight -= deltaTime * 2.0f;
			if (fWeight < 0.0f) fWeight = 0.0f;
		}

		if (objects.find("-Z") != objects.end()) {
			//피벗과 대상의 닫힌 상태 설정
			vec3 pivotPos = vec3(0.0f, 1.0f, 1.0f);    // 회전축이 되는 윗선
			vec3 startPos = vec3(0.0f, 1.0f, 0.0f);   // -Z면이 닫혀있을 때 원래 위치
			vec3 offset = startPos - pivotPos;         // 피벗으로부터의 방향과 거리 (0, -1, 0)

			//-Z면의 닫혀있을 때 원래 각도
			glm::quat startRot = glm::quat(vec3(0.0f, 0.0f, 0.0f));

			//닫힌 상태에서 얼마나 열 것인지 '회전 변화량(Delta)'을 정의 (X축으로 +90도 열기)
			glm::quat deltaStart = glm::quat(vec3(0.0f)); // 0도 변화 (닫힘)
			glm::quat deltaEnd = glm::quat(vec3(glm::radians(90.0f), 0.0f, 0.0f)); // 90도 변화 (열림)

			//fWeight에 따라 현재 프레임의 회전 변화량을 Slerp로 구합니다.
			glm::quat currentDeltaRot = glm::slerp(deltaStart, deltaEnd, fWeight);

			//오프셋 벡터에 '회전 변화량'을 곱하여 부드럽게 호를 그리는 새 위치를 구합니다.
			vec3 rotatedOffset = currentDeltaRot * offset;

			//최종 Transform 적용
			Transform* tr = objects["-Z"]->GetComponent<Transform>();
			tr->position = pivotPos + rotatedOffset;           // 피벗을 중심으로 이동한 위치
			tr->rotation = currentDeltaRot * startRot;         // 기존 세워진 각도에 변화량을 곱해줌
			tr->CalculateWorldMatrix();
		}

		if (isPZScaling) {
			bWeight += deltaTime * 2.0f;
			if (bWeight > 1.0f) bWeight = 1.0f;
		}
		else {
			bWeight -= deltaTime * 2.0f;
			if (bWeight < 0.0f) bWeight = 0.0f;
		}

		if (objects.find("+Z") != objects.end()) {
			vec3 startScale = vec3(1.0f, 1.0f, 1.0f);
			vec3 endScale = vec3(0.0f, 1.0f, 0.0f);

			Transform* tr = objects["+Z"]->GetComponent<Transform>();
			tr->scale = glm::mix(startScale, endScale, bWeight);
			tr->CalculateWorldMatrix();
		}
	}
}