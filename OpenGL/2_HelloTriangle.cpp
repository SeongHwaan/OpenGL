#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//화면 크기 설정
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//glsl로 vertex shader 설정
const char* vertexShaderSource = "#version 330 core\n"      //Opengl 따라 glsl의 버전 설정
"layout (location = 0) in vec3 aPos;\n"     //shader가 받을 입력의 위치를 지정. 0번째 위치에 aPos라는 변수를 받는다
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"     //gl_position은 glsl의 내장 변수. vertex shader의 출력 위치 벡터
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"layout (location = 0) out vec4 FragColor;\n"     //out은 qualifier 중 하나. 출력의 역할
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"        //gl_FragColor는 더 이상 사용되지 않고 out을 통해 fragment shader 설정
"}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // vertex shader 빌드 및 컴파일
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);       //glCreateShader는 정해진 파라미터를 입력 받고 만들어진 쉐이더의 ID를 int로 반환하는 함수
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);     //만들어둔 shader에 작성해둔 glsl을 연결한다
    glCompileShader(vertexShader);      //shader를 컴파일한다
    // 컴파일 에러 체크
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);       //Shader를 받아 특정 값을 반환하는 함수. 두 번째 파라미터의 조건을 확인하고 세 번째 파라미터에 숫자나 GL_TRUE, GL_FALSE를 반환
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);       //Shader의 log 반환(4번째 파라미터에). param:(1.shader, 2.maxLength, 3.*length, 4.*infoLog)
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader 빌드 및 컴파일
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // shader를 program에 연결
    unsigned int shaderProgram = glCreateProgram();     //shader 객체가 연결될 program 객체 생성
    glAttachShader(shaderProgram, vertexShader);        //program에 shader를 연결하기 전에 attach
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);                       //attach된 shader들을 program에 연결(link). program은 이미 shader에서 compile된 실행가능한 파일을 포함하고 있기에 shader 객체가 더 이상은 필요하지 않음
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);       //shader 객체 제거. 메모리에서 해제.
    glDeleteShader(fragmentShader);

    //vertex 값 설정
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    //index 값 설정
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);     /*Vertex Array Object 생성. 속성값을 저장하는 역할. meta data 같은 느낌.
                                      buffer를 바인딩하고, vertex data를 buffer에 복사하고, attribpointer를 설정하는 과정을 생략 가능 */
    glBindVertexArray(VAO);     //현재 context에 VAO를 바인딩. VBO나 EBO보다 먼저 바인딩이 요구된다

    glGenBuffers(1, &VBO);      //Vertex Buffer Object 생성. 실제 vertex data를 담당
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     //buffer를 target에 바인딩. target은 바인딩한 buffer에 의미를 부여해준다. GL_ARRAY_BUFFER는 vertex attributes
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);      //실제 data를 buffer에 복사. (target, data 크기, data, 관리 방법)

    glGenBuffers(1, &EBO);      //Elemnet Buffer Object 생성
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //buffer를 target에 바인딩
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);       /*OpenGL이 주어진 Vertex를 어떻게 해석할지 명령.
                        location(index), vertex 세트의 크기(vec3), data type, 정규화 유무, 세트 사이의 간격(stride), data 시작 위치의 offset*/
    glEnableVertexAttribArray(0);       //활성화(index)

    glBindBuffer(GL_ARRAY_BUFFER, 0);   //unbind buffer = change to default buffer. 다른 이유로 값이 변하지 않도록, 혹은 명시적인 buffer 입력의 종료 선언

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);     //EAO는 unbind 금지

    glBindVertexArray(0);       //unbind VAO

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // 매번 bind할 필요 없이 위에서 한 번만 bind해줘도 상관 없다. 좀 더 구조적인 설계를 위함
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    //삼각형 그리기 (mode, number of elements to be rendered, index 타입, indices들이 저장된 location)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //optional: 사용 후 해제
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}