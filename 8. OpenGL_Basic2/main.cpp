#include <gl/glew.h>
#include <gl/glfw3.h>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <random>
#include "Color.h"
#include "AppContext.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer2D.h"
#include "Director.h"
using namespace std;

template <typename T>
void ChangeParam(T* param, T value) {
	*param = value;
}

struct ScreenSize {
	int width;
	int height;
};

random_device rd;
default_random_engine dre{ rd() };
uniform_real_distribution<float> urd{0.0f, 1.0f};

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

	//시간 초기화
	ctx.time = glfwGetTime();

	////////////////////////메인 루프/////////////////////////
	Object* Square1 = Instantiate(ctx, "Square1");
	Transform* SquareTr1 = Square1->GetComponent<Transform>();
	SquareTr1->SetLocalPosition(0.5f, 0.5f, 0.0f);
	Square1->AddComponent<MeshRenderer2D>(1.0f, 1.0f, Color{ urd(dre) , urd(dre), urd(dre), 1.0f });

	Object* Square2 = Instantiate(ctx, "Square2");
	Transform* SquareTr2 = Square2->GetComponent<Transform>();
	SquareTr2->SetLocalPosition(-0.5f, 0.5f, 0.0f);
	Square2->AddComponent<MeshRenderer2D>(1.0f, 1.0f, Color{ urd(dre), urd(dre), urd(dre), 1.0f });

	Object* Square3 = Instantiate(ctx, "Square3");
	Transform* SquareTr3 = Square3->GetComponent<Transform>();
	SquareTr3->SetLocalPosition(-0.5f, -0.5f, 0.0f);
	Square3->AddComponent<MeshRenderer2D>(1.0f, 1.0f, Color{ urd(dre), urd(dre), urd(dre), 1.0f });

	Object* Square4 = Instantiate(ctx, "Square4");
	Transform* SquareTr4 = Square4->GetComponent<Transform>();
	SquareTr4->SetLocalPosition(0.5f, -0.5f, 0.0f);
	Square4->AddComponent<MeshRenderer2D>(1.0f, 1.0f, Color{ urd(dre), urd(dre), urd(dre), 1.0f });

	Object* DirectorObj = Instantiate(ctx, "Director");
	Director* directorSC = DirectorObj->AddComponent<Director>(ctx.inputManager);
	directorSC->SetPropertyValue("Square1", Square1);
	directorSC->SetPropertyValue("Square2", Square2);
	directorSC->SetPropertyValue("Square3", Square3);
	directorSC->SetPropertyValue("Square4", Square4);


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

		//Update 처리
		for (auto& obj : ctx.Hierarchy) {
			obj->Update(ctx.deltaTime);
		}

		if (!ctx.pendingHierarchy.empty()) {
			for (auto& newObj : ctx.pendingHierarchy) {
				ctx.Hierarchy.push_back(move(newObj));
			}
			ctx.pendingHierarchy.clear();
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
}

void DrawScene(GLFWwindow* window)
{
	AppContext* ctx = static_cast<AppContext*>(glfwGetWindowUserPointer(window));

	//버퍼 초기화
	glClearColor(ctx->bgColor.r, ctx->bgColor.g, ctx->bgColor.b, ctx->bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	//오브젝트 렌더링
	for (auto& obj : ctx->Hierarchy) {
		obj->Render();
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