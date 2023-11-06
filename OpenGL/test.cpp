#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Open

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



int main() {
	glfwInit();     //glfw를 사용하기 위해 호출하는 함수
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      //Opengl 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      //Opengl .3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      //profile -> core profile로 = 오래된 기능들 사용 안 함(glColor3f, glVertex3f)

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);     //window 생성(width, height, title, monitor(screen mode), share(resource))
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();        //glfw 종료 = 자원 정리
		return -1;
	}
	glfwMakeContextCurrent(window);     //Opengl 현재 thread를 window로 변경. Opengl은 state-machine



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))        //glad 초기화 및 작동 체크
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);     //Viewport 설정

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);      // 창의 크기가 변경될 때마다 콜백 함수를 호출하겠다고 GLFW에게 등록

	while (!glfwWindowShouldClose(window)) {		//main loop
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);       //어떤 색상으로 초기화할 것인지 설정. 아래 glClear의 설정값
		glClear(GL_COLOR_BUFFER_BIT);       //기존 컬러 버퍼 제거. 출력 내용이 변할 때마다 버퍼를 지워줘야 함. 없으면 새로운 컬러가 기존 컬러에 겹쳐지게 됨. 이 경우 특정 색상으로 지운 것(기존 색을 지우개가 아니라 물감으로 지운 느낌)

		glfwPollEvents();		//모든 event를 확인하며 정해진 콜백 함수 호출. 없으면 window조차 건들 수 없음 
		glfwSwapBuffers(window);		//컬러 버퍼 교체. 화면에 출력하는 기능
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {     //창의 크기가 조절될 때 호출되는 콜백 함수
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)       //입력을 처리하는 함수
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);     //window 종료 설정. 두 번째 파라미터는 int라 숫자도 가능
}