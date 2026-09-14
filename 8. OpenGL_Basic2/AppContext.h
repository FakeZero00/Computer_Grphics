#pragma once
#include <vector>
#include <memory>
#include "Color.h"
#include "InputManager.h"

class Object;

struct AppContext {
	Color bgColor = { 1.0f, 1.0f, 1.0f, 1.0f };			//배경색 초기화
	double time = 0.0;
	double deltaTime = 0.0;
	InputManager inputManager;							//입력 관리 객체

	vector<unique_ptr<Object>> Hierarchy;				//게임 오브젝트 계층 구조를 저장하는 벡터
	vector<unique_ptr<Object>> pendingHierarchy;		//새로 생성된 게임 오브젝트를 임시로 저장하는 벡터
};