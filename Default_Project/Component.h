#pragma once

//전방선언
class Object;

class Component {
public:
	//적용되어 있는 Object를 가리키는 포인터
	Object* gameObject = nullptr;
	bool hasStarted = false;

	//소멸자
	virtual ~Component() = default;

	//라이프 사이클 함수
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update(float deltaTime) {}
	virtual void Render() {}
};