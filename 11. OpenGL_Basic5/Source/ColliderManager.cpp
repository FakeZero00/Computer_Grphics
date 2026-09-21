#include "ColliderManager.h"
#include <vector>
#include <algorithm>
#include "Object.h"
#include "Component.h"
#include "Position2D.h"
using namespace std;

ColliderManager::ColliderManager(AppContext& ctx) : ctx(ctx) {}

bool ColliderManager::CheckCollision(BoxCollider2D* colA, BoxCollider2D* colB) {
	Position2D minA = colA->minPos;
	Position2D maxA = colA->maxPos;
	Position2D minB = colB->minPos;
	Position2D maxB = colB->maxPos;

	if (minA.x > maxB.x || maxA.x < minB.x) return false; // X축 충돌 없음
	if (minA.y > maxB.y || maxA.y < minB.y) return false; // Y축 충돌 없음

	return true;
}

void ColliderManager::Update() {
	vector<BoxCollider2D*>& CollisionObjects = ctx.CollisionObjects;

	for (size_t i = 0; i < CollisionObjects.size(); ++i) {
		for (size_t j = i + 1; j < CollisionObjects.size(); ++j) {
			BoxCollider2D* colA = CollisionObjects[i];
			BoxCollider2D* colB = CollisionObjects[j];

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