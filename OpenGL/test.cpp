#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Open

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



int main() {
	glfwInit();     //glfw¸¦ »ç¿ëÇÏ±â À§ÇØ È£ÃâÇÏ´Â ÇÔ¼ö
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      //Opengl 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      //Opengl .3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      //profile -> core profile·Î = ¿À·¡µÈ ±â´Éµé »ç¿ë ¾È ÇÔ(glColor3f, glVertex3f)

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);     //window »ý¼º(width, height, title, monitor(screen mode), share(resource))
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();        //glfw Á¾·á = ÀÚ¿ø Á¤¸®
		return -1;
	}
	glfwMakeContextCurrent(window);     //Opengl ÇöÀç thread¸¦ window·Î º¯°æ. OpenglÀº state-machine



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))        //glad ÃÊ±âÈ­ ¹× ÀÛµ¿ Ã¼Å©
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);     //Viewport ¼³Á¤

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);      // Ã¢ÀÇ Å©±â°¡ º¯°æµÉ ¶§¸¶´Ù ÄÝ¹é ÇÔ¼ö¸¦ È£ÃâÇÏ°Ú´Ù°í GLFW¿¡°Ô µî·Ï

	while (!glfwWindowShouldClose(window)) {		//main loop
		processInput(window);

<<<<<<< HEAD
        glfwPollEvents();                       //every event. ì—†ìœ¼ë©´ windowì¡°ì°¨ ê±´ë“¤ ìˆ˜ ì—†ìŒ
        glfwSwapBuffers(window);
    }
=======
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);       //¾î¶² »ö»óÀ¸·Î ÃÊ±âÈ­ÇÒ °ÍÀÎÁö ¼³Á¤. ¾Æ·¡ glClearÀÇ ¼³Á¤°ª
		glClear(GL_COLOR_BUFFER_BIT);       //±âÁ¸ ÄÃ·¯ ¹öÆÛ Á¦°Å. Ãâ·Â ³»¿ëÀÌ º¯ÇÒ ¶§¸¶´Ù ¹öÆÛ¸¦ Áö¿öÁà¾ß ÇÔ. ¾øÀ¸¸é »õ·Î¿î ÄÃ·¯°¡ ±âÁ¸ ÄÃ·¯¿¡ °ãÃÄÁö°Ô µÊ. ÀÌ °æ¿ì Æ¯Á¤ »ö»óÀ¸·Î Áö¿î °Í(±âÁ¸ »öÀ» Áö¿ì°³°¡ ¾Æ´Ï¶ó ¹°°¨À¸·Î Áö¿î ´À³¦)
>>>>>>> fb15b807c61a0d50770d14f91812583183e78be0

		glfwPollEvents();		//¸ðµç event¸¦ È®ÀÎÇÏ¸ç Á¤ÇØÁø ÄÝ¹é ÇÔ¼ö È£Ãâ. ¾øÀ¸¸é windowÁ¶Â÷ °Çµé ¼ö ¾øÀ½ 
		glfwSwapBuffers(window);		//ÄÃ·¯ ¹öÆÛ ±³Ã¼. È­¸é¿¡ Ãâ·ÂÇÏ´Â ±â´É
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {     //Ã¢ÀÇ Å©±â°¡ Á¶ÀýµÉ ¶§ È£ÃâµÇ´Â ÄÝ¹é ÇÔ¼ö
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)       //ÀÔ·ÂÀ» Ã³¸®ÇÏ´Â ÇÔ¼ö
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);     //window Á¾·á ¼³Á¤. µÎ ¹øÂ° ÆÄ¶ó¹ÌÅÍ´Â int¶ó ¼ýÀÚµµ °¡´É
}