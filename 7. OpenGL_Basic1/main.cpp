#include <gl/glew.h>
#include <gl/glfw3.h>
#include <iostream>
#include <random>
using namespace std;

template <typename T>
void ChangeParam(T* param, T value) {
	*param = value;
}

typedef struct color {
	float r;
	float g;
	float b;
	float a;
} Color;

struct AppContext {
	Color bgColor = { 1.0f, 1.0f, 1.0f, 1.0f }; //배경색 초기화
	bool isRdAnim = false;
	double time = 0.0;
};

random_device rd;
default_random_engine dre{ rd() };
uniform_real_distribution<float> ufd(0.0f, 1.0f);


void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void InputProcess(GLFWwindow* window);
void DrawScene(GLFWwindow* window);

int main() {
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
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
	if (!window) {
		cerr << "윈도우 생성 실패" << endl;
		glfwTerminate();
		return -1;
	}

	//컨텍스트 설정
	glfwMakeContextCurrent(window);

	//컨텍스트 변수 생성, 윈도우 객체에 연결
	AppContext ctx;
	glfwSetWindowUserPointer(window, &ctx);

	//GLEW 초기화
	glewExperimental = GL_TRUE;	//최신 기능 사용
	if (glewInit() != GLEW_OK) {
		cerr << "GLEW 초기화 실패" << endl;
		glfwTerminate();
		return -1;
	}

	//키보드 입력 콜백 함수 설정
	glfwSetKeyCallback(window, KeyCallback);

	glViewport(0, 0, 800, 600);	//뷰포트 설정

	//메인 루프
	while (!glfwWindowShouldClose(window)) {
		//시간 계산
		ctx.time = glfwGetTime();

		//이벤트 처리
		glfwPollEvents();

		//입력 처리
		InputProcess(window);

		////////////////////////게임 루프////////////////////////

		if (ctx.isRdAnim) {
			if (ctx.time >= 3.0) {
				ChangeParam(&ctx.bgColor, Color{ ufd(dre), ufd(dre), ufd(dre), 1.0f });
				glfwSetTime(0.0);
				ctx.time = 0.0;
			}
		}

		////////////////////////////////////////////////////////

		//화면 렌더링
		DrawScene(window);

		//버퍼 스왑
		glfwSwapBuffers(window);
	}

	//리소스 해제
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			default:
				break;
		}
	}
}

void InputProcess(GLFWwindow* window)
{
	AppContext* ctx = static_cast<AppContext*>(glfwGetWindowUserPointer(window));

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		ChangeParam(&ctx->bgColor, Color{ 0.0f, 1.0f, 1.0f, 1.0f });
	else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		ChangeParam(&ctx->bgColor, Color{ 1.0f, 0.0f, 1.0f, 1.0f });
	else if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		ChangeParam(&ctx->bgColor, Color{ 1.0f, 1.0f, 0.0f, 1.0f });
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		ChangeParam(&ctx->bgColor, Color{ ufd(dre), ufd(dre), ufd(dre), 1.0f});
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		ChangeParam(&ctx->bgColor, Color{ 0.5f, 0.5f, 0.5f, 1.0f });
	else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		ChangeParam(&ctx->bgColor, Color{ 0.0f, 0.0f, 0.0f, 1.0f });
	else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		ChangeParam(&ctx->isRdAnim, true);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		ChangeParam(&ctx->isRdAnim, false);
}

void DrawScene(GLFWwindow* window)
{
	AppContext* ctx = static_cast<AppContext*>(glfwGetWindowUserPointer(window));

	glClearColor(ctx->bgColor.r, ctx->bgColor.g, ctx->bgColor.b, ctx->bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}