#include "SquareMovement.h"
#include "Transform.h"
#include "Position2D.h"
#include "Object.h"
#include "MeshRenderer2D.h"
#include "BoxCollider2D.h"
#include "InputManager.h"
#include <random>

void SquareMovement::Seperate() {
	Transform* tr = gameObject->GetComponent<Transform>();
	cout << tr->parent->children.size() << endl;
	if (tr->parent->children.size() <= 19) {
		MeshRenderer2D* mr = gameObject->GetComponent<MeshRenderer2D>();
		BoxCollider2D* bc = gameObject->GetComponent<BoxCollider2D>();
		float width = mr->width;
		float height = mr->height;

		width /= 2.0f;

		//기존 오브젝트 크기 조정
		mr->SetSize(width, height);
		bc->SetSize(width, height);
		tr->position.x -= width / 2.0f;

		tr->CalculateWorldPosition();
		bc->RecalculateCollision();

		//새로운 오브젝트 생성
		random_device rd;
		default_random_engine dre{ rd() };
		uniform_real_distribution<float> urd{ 0.0f, 1.0f };

		Object* nSquare = tr->parent->gameObject->Instantiate(string{ "Square (Seperated)" });
		Transform* nSquareTr = nSquare->GetComponent<Transform>();
		nSquareTr->SetLocalPosition(tr->position.x + width, tr->position.y, 0.0f);
		nSquare->AddComponent<MeshRenderer2D>(width, height, Color{ urd(dre), urd(dre), urd(dre), 1.0f });
		nSquare->AddComponent<BoxCollider2D>(width, height);
		nSquare->AddComponent<SquareMovement>();
	}
}

void SquareMovement::OnTriggerStay(Object* other) {
	if (combineReady) {
		cout << "Trigger stay with: " << gameObject->name << endl;
		//두 오브젝트를 합치기
		MeshRenderer2D* mr1 = gameObject->GetComponent<MeshRenderer2D>();
		MeshRenderer2D* mr2 = other->GetComponent<MeshRenderer2D>();
		
		Position2D minPos1 = mr1->minPos;
		Position2D maxPos1 = mr1->maxPos;
		Position2D minPos2 = mr2->minPos;
		Position2D maxPos2 = mr2->maxPos;

		Position2D newMinPos{ std::min(minPos1.x, minPos2.x), std::min(minPos1.y, minPos2.y) };
		Position2D newMaxPos{ std::max(maxPos1.x, maxPos2.x), std::max(maxPos1.y, maxPos2.y) };

		mr1->minPos = newMinPos;
		mr1->maxPos = newMaxPos;

		mr1->SetSize(newMaxPos.x - newMinPos.x, newMaxPos.y - newMinPos.y);
		
		Transform* tr1 = gameObject->GetComponent<Transform>();
		tr1->position = { (newMinPos.x + newMaxPos.x) / 2.0f, (newMinPos.y + newMaxPos.y) / 2.0f, 0.0f };
		tr1->CalculateWorldPosition();
		
		BoxCollider2D* bc1 = gameObject->GetComponent<BoxCollider2D>();
		bc1->SetSize(newMaxPos.x - newMinPos.x, newMaxPos.y - newMinPos.y);
		bc1->RecalculateCollision();

		//다른 오브젝트 제거
		other->Destroy();

		isMoving = false;
		combineReady = false;
	}
}

void SquareMovement::Update(float deltaTime) {
	if (isMoving) {
		Transform* tr = gameObject->GetComponent<Transform>();
		BoxCollider2D* bc = gameObject->GetComponent<BoxCollider2D>();
		InputManager& inputManager = gameObject->ctx.inputManager;

		tr->position.x = inputManager.GetMouseX();
		tr->position.y = inputManager.GetMouseY();

		tr->CalculateWorldPosition();
		bc->RecalculateCollision();
	}
}