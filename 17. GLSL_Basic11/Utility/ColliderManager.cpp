#include "ColliderManager.h"
#include <vector>
#include <algorithm>
#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include <iostream>
using namespace std;

ColliderManager::ColliderManager(AppContext& ctx) : ctx(ctx) {}

bool ColliderManager::CheckCollision(Collider* colA, Collider* colB) {
	//1. Box vs Box 충돌 체크
	if (colA->type == ColliderType::Box && colB->type == ColliderType::Box) {
		return CheckBoxBox(static_cast<BoxCollider*>(colA), static_cast<BoxCollider*>(colB));
	}

	//2. Sphere vs Sphere 충돌 체크
	else if (colA->type == ColliderType::Sphere && colB->type == ColliderType::Sphere) {
		//임시
		return false;
	}

	//3. Box vs Sphere 충돌 체크
	else if ((colA->type == ColliderType::Box && colB->type == ColliderType::Sphere) ||
		(colA->type == ColliderType::Sphere && colB->type == ColliderType::Box)) {
		//임시
		return false;
	}

	//4. 그 외의 경우
	else return false;
}

bool ColliderManager::CheckBoxBox(BoxCollider* colA, BoxCollider* colB) {
	vec3 minA = colA->minPos;
	vec3 maxA = colA->maxPos;
	vec3 minB = colB->minPos;
	vec3 maxB = colB->maxPos;

	if (minA.x > maxB.x || maxA.x < minB.x) return false;
	if (minA.y > maxB.y || maxA.y < minB.y) return false;
	if (minA.z > maxB.z || maxA.z < minB.z) return false;

	return true;
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