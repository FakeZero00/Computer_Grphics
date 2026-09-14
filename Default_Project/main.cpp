#include <gl/glew.h>
#include <gl/glfw3.h>
#include <iostream>
using namespace std;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void InputProcess(GLFWwindow* window);
void DrawScene();

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
		//이벤트 처리
		glfwPollEvents();

		//입력 처리
		InputProcess(window);

		//화면 렌더링
		DrawScene();

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void DrawScene()
{
	//화면 지우기
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}