#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Component.h"
#include "Transform.h"
using namespace std;

class Object {
public:
	string name = "GameObject";

	Object(string str) : name(str) {
		//Transform 컴포넌트 생성 및 추가
		auto transform = make_unique<Transform>();
		transform->gameObject = this; //Transform의 gameObject를 현재 Object로 설정

		components.push_back(move(transform)); //컴포넌트 벡터에 추가
	}

	template <typename T, typename... Args>
	T* AddComponent(Args&&... args) {
		T* newComponent = new T(forward<Args>(args)...);

		//본 오브젝트를 부모 오브젝트로 설정
		newComponent->gameObject = this;
		components.push_back(unique_ptr<Component>(newComponent));

		//추가될 때, 컴포넌트의 Awake 호출
		newComponent->Awake();
		return newComponent;
	}

	template <typename T>
	T* GetComponent() {
		for (auto& comp : components) {
			T* target = dynamic_cast<T*>(comp.get());
			if (target != nullptr) return target;
		}

		return nullptr;
	}

	void Awake() {
		for (auto& comp : components) {
			comp->Awake();
		}
	}

	void Start() {
		for (auto& comp : components) {
			comp->Start();
		}
	}

	void Update(double deltaTime) {
		for (auto& comp : components) {
			if (!comp->hasStarted) {
				comp->Start();
				comp->hasStarted = true;
			}

			comp->Update(static_cast<float>(deltaTime));
		}
	}

	void Render() {
		for (auto& comp : components) {
			comp->Render();
		}
	}

private:
	//컴포넌트들을 소유하고 있는 벡터
	vector<unique_ptr<Component>> components;
};