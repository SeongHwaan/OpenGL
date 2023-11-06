#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Open

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



int main() {
	glfwInit();     //glfw�� ����ϱ� ���� ȣ���ϴ� �Լ�
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      //Opengl 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      //Opengl .3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      //profile -> core profile�� = ������ ��ɵ� ��� �� ��(glColor3f, glVertex3f)

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);     //window ����(width, height, title, monitor(screen mode), share(resource))
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();        //glfw ���� = �ڿ� ����
		return -1;
	}
	glfwMakeContextCurrent(window);     //Opengl ���� thread�� window�� ����. Opengl�� state-machine



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))        //glad �ʱ�ȭ �� �۵� üũ
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);     //Viewport ����

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);      // â�� ũ�Ⱑ ����� ������ �ݹ� �Լ��� ȣ���ϰڴٰ� GLFW���� ���

	while (!glfwWindowShouldClose(window)) {		//main loop
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);       //� �������� �ʱ�ȭ�� ������ ����. �Ʒ� glClear�� ������
		glClear(GL_COLOR_BUFFER_BIT);       //���� �÷� ���� ����. ��� ������ ���� ������ ���۸� ������� ��. ������ ���ο� �÷��� ���� �÷��� �������� ��. �� ��� Ư�� �������� ���� ��(���� ���� ���찳�� �ƴ϶� �������� ���� ����)

		glfwPollEvents();		//��� event�� Ȯ���ϸ� ������ �ݹ� �Լ� ȣ��. ������ window���� �ǵ� �� ���� 
		glfwSwapBuffers(window);		//�÷� ���� ��ü. ȭ�鿡 ����ϴ� ���
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {     //â�� ũ�Ⱑ ������ �� ȣ��Ǵ� �ݹ� �Լ�
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)       //�Է��� ó���ϴ� �Լ�
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);     //window ���� ����. �� ��° �Ķ���ʹ� int�� ���ڵ� ����
}