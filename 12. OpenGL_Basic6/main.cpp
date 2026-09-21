#include "Common.h"
using namespace std;

/////////////스크립트 임포트/////////////
#include "SquareManager.h"
////////////////////////////////////////

template <typename T>
void ChangeParam(T* param, T value) {
	*param = value;
}

struct ScreenSize {
	int width;
	int height;
};

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void InputProcess(GLFWwindow* window);
void DrawScene(GLFWwindow* window);
Object* Instantiate(AppContext& ctx, string name);
Object* FindObject(AppContext& ctx, string name);

int main() {
	//스크린 사이즈 설정
	ScreenSize screenSize{800, 800};

	//GLFW 초기화
	if (!glfwInit()) {
		cerr << "GLFW 초기화 실패" << endl;
		return -1;
	}

	//OpenGL 버전 설정
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//윈도우 생성
	GLFWwindow* window = glfwCreateWindow(screenSize.width, screenSize.height, "OpenGL Window", nullptr, nullptr);
	if (!window) {
		cerr << "윈도우 생성 실패" << endl;
		glfwTerminate();
		return -1;
	}

	//컨텍스트 설정
	glfwMakeContextCurrent(window);

	//GLEW 초기화
	glewExperimental = GL_TRUE;	//최신 기능 사용
	if (glewInit() != GLEW_OK) {
		cerr << "GLEW 초기화 실패" << endl;
		glfwTerminate();
		return -1;
	}

	//////////////////사용자 정의 초기화////////////////////

	//외부 입력 콜백 함수 설정
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);

	//뷰포트 설정
	glViewport(0, 0, screenSize.width, screenSize.height);

	//컨텍스트 변수 생성, 윈도우 객체에 연결
	AppContext ctx;
	glfwSetWindowUserPointer(window, &ctx);
	ctx.bgColor = { 0.2f, 0.2f, 0.2f, 1.0f }; //배경색 설정

	ColliderManager colliderManager(ctx);

	//시간 초기화
	ctx.time = glfwGetTime();

	////////////////////////메인 루프////////////////////////

	///////////////////게임 오브젝트 생성////////////////////
	Object* manager = Instantiate(ctx, "Manager");
	manager->AddComponent<SquareManager>();

	/////////////////////////////////////////////////////////

	while (!glfwWindowShouldClose(window)) {
		//시간 계산
		double currentTime = glfwGetTime();
		ctx.deltaTime = currentTime - ctx.time;
		ctx.time = currentTime;

		//입력 처리
		ctx.inputManager.Update();
		InputProcess(window);

		//이벤트 처리
		glfwPollEvents();

		//Start 처리
		for (auto& obj : ctx.Hierarchy) {
			if (obj->isValid && !obj->isStarted) {
				obj->isStarted = true;
				obj->Start();
			}
		}

		//Update 처리
		for (auto& obj : ctx.Hierarchy) {
			if (obj->isValid) obj->Update(ctx.deltaTime);
		}

		//충돌 감지
		colliderManager.Update();

		//추가할 오브젝트가 있다면 Hierarchy에 추가
		if (!ctx.pendingHierarchy.empty()) {
			for (auto& newObj : ctx.pendingHierarchy) {
				ctx.Hierarchy.push_back(move(newObj));
			}
			ctx.pendingHierarchy.clear();
		}

		//추가할 충돌 감지 콜리전이 있다면 CollisionObjects에 추가
		if (!ctx.pendingCollisionObjects.empty()) {
			for (auto& newCol : ctx.pendingCollisionObjects) {
				ctx.CollisionObjects.push_back(newCol);
			}
			ctx.pendingCollisionObjects.clear();
		}

		//제거할 오브젝트가 있다면 Hierarchy에서 제거
		if (!ctx.pendingDestroyObjects.empty()) {
			for (auto& targetObj : ctx.pendingDestroyObjects) {
				//CollisionObjects에서도 제거
				auto& collist = ctx.CollisionObjects;
				collist.erase(remove_if(collist.begin(), collist.end(),
					[targetObj](BoxCollider2D* col) {
						return col->gameObject == targetObj;
					}),
					collist.end());

				//부모 자식 관계 정리
				Transform* targetTr = targetObj->GetComponent<Transform>();
				if (targetTr && targetTr->parent != nullptr) {
					auto& siblings = targetTr->parent->children;
					siblings.erase(remove(siblings.begin(), siblings.end(), targetTr), siblings.end());
				}

				//Hierarchy에서 제거
				auto& hierarchy = ctx.Hierarchy;
				hierarchy.erase(remove_if(hierarchy.begin(), hierarchy.end(),
					[targetObj](const unique_ptr<Object>& obj) { return obj.get() == targetObj; }),
					hierarchy.end());
			}
			ctx.pendingDestroyObjects.clear();
		}

		//화면 렌더링
		DrawScene(window);
	}

	/////////////////////////루프 종료/////////////////////////
	//리소스 해제
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	AppContext* ctx = static_cast<AppContext*>(glfwGetWindowUserPointer(window));
	if (!ctx) return;
	
	if (action == GLFW_PRESS) ctx->inputManager.SetKey(key, true);
	else if (action == GLFW_RELEASE) ctx->inputManager.SetKey(key, false);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	AppContext* ctx = static_cast<AppContext*>(glfwGetWindowUserPointer(window));
	if (!ctx) return;

	if (action == GLFW_PRESS) ctx->inputManager.SetKey(button, true);
	else if (action == GLFW_RELEASE) ctx->inputManager.SetKey(button, false);
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	AppContext* ctx = static_cast<AppContext*>(glfwGetWindowUserPointer(window));
	if (!ctx) return;

	//마우스 좌표를 OpenGL 좌표계로 변환
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	float glX = (xpos / width) * 2.0f - 1.0f;
	float glY = 1.0f - (ypos / height) * 2.0f; //Y축 반전
	ctx->inputManager.SetMousePosition(glX, glY);
}

void InputProcess(GLFWwindow* window)
{
	AppContext* ctx = static_cast<AppContext*>(glfwGetWindowUserPointer(window));

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void DrawScene(GLFWwindow* window)
{
	AppContext* ctx = static_cast<AppContext*>(glfwGetWindowUserPointer(window));

	//버퍼 초기화
	glClearColor(ctx->bgColor.r, ctx->bgColor.g, ctx->bgColor.b, ctx->bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	//렌더링 큐 생성
	vector<Object*> renderQueue;
	renderQueue.reserve(ctx->Hierarchy.size());
	for (auto& obj : ctx->Hierarchy) {
		renderQueue.push_back(obj.get());
	}

	//렌더링 큐 정렬 (Z값 기준. Z값이 클 수록 나중에 렌더링)
	stable_sort(renderQueue.begin(), renderQueue.end(),
		[](Object* a, Object* b) {
			Transform* trA = a->GetComponent<Transform>();
			Transform* trB = b->GetComponent<Transform>();
			if (trA && trB) {
				return trA->worldPosition.z < trB->worldPosition.z;
			}
			return false;
		});

	//오브젝트 렌더링
	for (auto& obj : renderQueue) {
		if(obj->isValid) obj->Render();
	}

	//버퍼 스왑
	glfwSwapBuffers(window);
}

Object* Instantiate(AppContext& ctx, string name) {
	auto newObj = make_unique<Object>(ctx, name);
	Object* ptr = newObj.get();

	ctx.Hierarchy.push_back(move(newObj));
	return ptr;
}

Object* FindObject(AppContext& ctx, string name) {
	for (auto& obj : ctx.Hierarchy) {
		if (obj->name == name) {
			return obj.get();
		}
	}
	return nullptr;
}