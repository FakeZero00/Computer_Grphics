#pragma once
#include <map>
#include <string>
#include <iostream>
using namespace std;

//전방선언
class Object;

enum class PropertyType {
	Float,
	Int,
	String,
	Object,
	ComponentPtr
};

struct Property {
	PropertyType type;
	void* dataPtr;
};

class Component {
public:
	//적용되어 있는 Object를 가리키는 포인터
	Object* gameObject = nullptr;
	bool hasStarted = false;

	//변수들을 저장하는 맵
	map<string, Property> properties;

	//소멸자
	virtual ~Component() = default;

	//라이프 사이클 함수
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update(float deltaTime) {}
	virtual void Render() {}

	//아웃렛 접속 함수
	template <typename T>
	void Expose(string name, T* varAddr) {
		PropertyType pType;

		if constexpr (is_same_v<T, float>) pType = PropertyType::Float;
		else if constexpr (is_same_v<T, int>) pType = PropertyType::Int;
		else if constexpr (is_same_v<T, string>) pType = PropertyType::String;
		else if constexpr (is_same_v<T, Object>) pType = PropertyType::Object;
		else pType = PropertyType::ComponentPtr; //기타 타입은 ComponentPtr로 처리

		properties[name] = { pType, static_cast<void*>(varAddr) };
	}

	template <typename T>
	void SetPropertyValue(string name, T value) {
		if (properties.find(name) == properties.end()) {
			cout << "Property " << name << " not found!" << endl;
		}

		T* ptr = static_cast<T*>(properties[name].dataPtr);
		*ptr = value;
	}
};