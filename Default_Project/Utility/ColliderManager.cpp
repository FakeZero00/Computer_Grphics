#include "ColliderManager.h"
#include <vector>
#include <algorithm>
#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include <iostream>
#include <cmath>
using namespace std;

ColliderManager::ColliderManager(AppContext& ctx) : ctx(ctx) {}

bool ColliderManager::CheckCollision(Collider* colA, Collider* colB) {
	//1. Box vs Box 충돌 체크
	if (colA->type == ColliderType::Box && colB->type == ColliderType::Box) {
		return CheckBoxBox(static_cast<BoxCollider*>(colA), static_cast<BoxCollider*>(colB));
	}

	//2. Sphere vs Sphere 충돌 체크
	else if (colA->type == ColliderType::Sphere && colB->type == ColliderType::Sphere) {
		return CheckSphereSphere(static_cast<SphereCollider*>(colA), static_cast<SphereCollider*>(colB));
	}

	//3. Box vs Sphere 충돌 체크
	else if (colA->type == ColliderType::Box && colB->type == ColliderType::Sphere) {
		return CheckBoxSphere(static_cast<BoxCollider*>(colA), static_cast<SphereCollider*>(colB));
	}
	else if (colA->type == ColliderType::Sphere && colB->type == ColliderType::Box) {
		return CheckBoxSphere(static_cast<BoxCollider*>(colB), static_cast<SphereCollider*>(colA));
	}

	//4. 그 외의 경우
	else return false;
}

bool ColliderManager::CheckBoxBox(BoxCollider* colA, BoxCollider* colB) {
	Transform* trA = colA->gameObject->GetComponent<Transform>();
	Transform* trB = colB->gameObject->GetComponent<Transform>();
	
	// 각 박스의 로컬 중심점 및 반-크기(Half-Extents) 구하기
	vec3 localCenterA = (colA->localMin + colA->localMax) * 0.5f;
	vec3 localExtentA = (colA->localMax - colA->localMin) * 0.5f;

	vec3 localCenterB = (colB->localMin + colB->localMax) * 0.5f;
	vec3 localExtentB = (colB->localMax - colB->localMin) * 0.5f;

	// 월드 중심점 계산
	vec3 centerA = vec3(trA->worldMatrix * vec4(localCenterA, 1.0f));
	vec3 centerB = vec3(trB->worldMatrix * vec4(localCenterB, 1.0f));
	vec3 dist = centerB - centerA;	// 두 박스 중심 간의 거리 벡터

	// 각 박스의 축(로컬 축)과 스케일 반영된 반-크기 산출
	vec3 A[3], B[3];
	vec3 a, b;	// 월드 스케일이 적용된 반-크기

	for (int i = 0; i < 3; ++i) {
		vec3 axisA = vec3(trA->worldMatrix[i]);
		a[i] = localExtentA[i] * glm::length(axisA);
		A[i] = glm::normalize(axisA);

		vec3 axisB = vec3(trB->worldMatrix[i]);
		b[i] = localExtentB[i] * glm::length(axisB);
		B[i] = glm::normalize(axisB);
	}

	// 회전 행렬 R_ij = A_i dot B_j 및 절대값 행렬 계산
	const float EPSILON = 1e-5f;	// 작은 값으로 0 근처의 수치 오차 방지
	float R[3][3], AbsR[3][3];

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			R[i][j] = glm::dot(A[i], B[j]);
			AbsR[i][j] = std::abs(R[i][j]) + EPSILON;
		}
	}

	// A 기준 좌표계에서의 중심 간 거리를 투영
	vec3 t = vec3(glm::dot(dist, A[0]), glm::dot(dist, A[1]), glm::dot(dist, A[2]));

	// 15개의 분리축 투영 검사
	// A의 3개 축 검사 (A0, A1, A2)
	for (int i = 0; i < 3; ++i) {
		float ra = a[i];
		float rb = b[0] * AbsR[i][0] + b[1] * AbsR[i][1] + b[2] * AbsR[i][2];
		if (std::abs(t[i]) > ra + rb) return false;
	}

	// B의 3개 축 검사 (B0, B1, B2)
	for (int i = 0; i < 3; ++i) {
		float ra = a[0] * AbsR[0][i] + a[1] * AbsR[1][i] + a[2] * AbsR[2][i];
		float rb = b[i];
		float term = std::abs(glm::dot(dist, B[i]));
		if (term > ra + rb) return false;
	}

	//외적 축 9개 검사
	// A0 x B0
	if (std::abs(t[2] * R[1][0] - t[1] * R[2][0]) > a[1] * AbsR[2][0] + a[2] * AbsR[1][0] + b[1] * AbsR[0][2] + b[2] * AbsR[0][1]) return false;
	// A0 x B1
	if (std::abs(t[2] * R[1][1] - t[1] * R[2][1]) > a[1] * AbsR[2][1] + a[2] * AbsR[1][1] + b[0] * AbsR[0][2] + b[2] * AbsR[0][0]) return false;
	// A0 x B2
	if (std::abs(t[2] * R[1][2] - t[1] * R[2][2]) > a[1] * AbsR[2][2] + a[2] * AbsR[1][2] + b[0] * AbsR[0][1] + b[1] * AbsR[0][0]) return false;

	// A1 x B0
	if (std::abs(t[0] * R[2][0] - t[2] * R[0][0]) > a[0] * AbsR[2][0] + a[2] * AbsR[0][0] + b[1] * AbsR[1][2] + b[2] * AbsR[1][1]) return false;
	// A1 x B1
	if (std::abs(t[0] * R[2][1] - t[2] * R[0][1]) > a[0] * AbsR[2][1] + a[2] * AbsR[0][1] + b[0] * AbsR[1][2] + b[2] * AbsR[1][0]) return false;
	// A1 x B2
	if (std::abs(t[0] * R[2][2] - t[2] * R[0][2]) > a[0] * AbsR[2][2] + a[2] * AbsR[0][2] + b[0] * AbsR[1][1] + b[1] * AbsR[1][0]) return false;

	// A2 x B0
	if (std::abs(t[1] * R[0][0] - t[0] * R[1][0]) > a[0] * AbsR[1][0] + a[1] * AbsR[0][0] + b[1] * AbsR[2][2] + b[2] * AbsR[2][1]) return false;
	// A2 x B1
	if (std::abs(t[1] * R[0][1] - t[0] * R[1][1]) > a[0] * AbsR[1][1] + a[1] * AbsR[0][1] + b[0] * AbsR[2][2] + b[2] * AbsR[2][0]) return false;
	// A2 x B2
	if (std::abs(t[1] * R[0][2] - t[0] * R[1][2]) > a[0] * AbsR[1][2] + a[1] * AbsR[0][2] + b[0] * AbsR[2][1] + b[1] * AbsR[2][0]) return false;

	// 15개 축 중 분리축을 찾지 못했다면 두 OBB는 충돌 상태!
	return true;
}

bool ColliderManager::CheckSphereSphere(SphereCollider* colA, SphereCollider* colB) {
	float dist = glm::distance(colA->worldCenter, colB->worldCenter);
	return dist <= (colA->worldRadius + colB->worldRadius);
}

bool ColliderManager::CheckBoxSphere(BoxCollider* box, SphereCollider* sphere) {
	Transform* boxTr = box->gameObject->GetComponent<Transform>();

	// 구체의 월드 좌표를 박스 오브젝트의 로컬 좌표계로 역변환
	mat4 invBoxMatrix = glm::inverse(boxTr->worldMatrix);
	vec3 localSphereCenter = vec3(invBoxMatrix * vec4(sphere->worldCenter, 1.0f));

	// AABB 박스 안에서 구체의 중심점과 가장 가까운 x,y,z 좌표를 찾음 (Clamp)
	float closestX = glm::clamp(localSphereCenter.x, box->localMin.x, box->localMax.x);
	float closestY = glm::clamp(localSphereCenter.y, box->localMin.y, box->localMax.y);
	float closestZ = glm::clamp(localSphereCenter.z, box->localMin.z, box->localMax.z);

	vec3 localClosestPoint = vec3(closestX, closestY, closestZ);

	// 가장 가까운 로컬 점을 다시 월드 좌표로 복원, 구체 월드 중심과 거리 비교
	vec3 worldClosestPoint = vec3(boxTr->worldMatrix * vec4(localClosestPoint, 1.0f));
	float dist = glm::distance(worldClosestPoint, sphere->worldCenter);

	return dist <= sphere->worldRadius;
}

void ColliderManager::Update() {
	vector<Collider*>& CollisionObjects = ctx.CollisionObjects;

	for (size_t i = 0; i < CollisionObjects.size(); ++i) {
		for (size_t j = i + 1; j < CollisionObjects.size(); ++j) {
			Collider* colA = CollisionObjects[i];
			Collider* colB = CollisionObjects[j];

			if (!colA->gameObject->isValid) continue;
			if (!colB->gameObject->isValid) continue;

			if (colA && colB) {
				bool isColliding = CheckCollision(colA, colB);

				//A 입장에서의 B와 충돌 처리
				auto it = find(colA->collidingColliders.begin(), colA->collidingColliders.end(), colB);
				bool aAlreadyColliding = (it != colA->collidingColliders.end());
				if (isColliding) {
					if (!aAlreadyColliding) {
						//최초 충돌 발생
						colA->collidingColliders.push_back(colB);
						for (auto& comp : colA->gameObject->components) {
							comp->OnTriggerEnter(colB->gameObject);
						}
					}
					else {
						//계속 충돌 중
						for (auto& comp : colA->gameObject->components) {
							comp->OnTriggerStay(colB->gameObject);
						}
					}
				}
				else {
					if (aAlreadyColliding) {
						//충돌 종료
						colA->collidingColliders.erase(it);
						for (auto& comp : colA->gameObject->components) {
							comp->OnTriggerExit(colB->gameObject);
						}
					}
				}

				//B 입장에서의 A와 충돌 처리
				it = find(colB->collidingColliders.begin(), colB->collidingColliders.end(), colA);
				bool bAlreadyColliding = (it != colB->collidingColliders.end());
				if (isColliding) {
					if (!bAlreadyColliding) {
						//최초 충돌 발생
						colB->collidingColliders.push_back(colA);
						for (auto& comp : colB->gameObject->components) {
							comp->OnTriggerEnter(colA->gameObject);
						}
					}
					else {
						//계속 충돌 중
						for (auto& comp : colB->gameObject->components) {
							comp->OnTriggerStay(colA->gameObject);
						}
					}
				}
				else {
					if (bAlreadyColliding) {
						//충돌 종료
						colB->collidingColliders.erase(it);
						for (auto& comp : colB->gameObject->components) {
							comp->OnTriggerExit(colA->gameObject);
						}
					}
				}
			}
		}
	}
}