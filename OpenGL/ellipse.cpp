#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const int numVertices = 100;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

void drawEllipse(float centerX, float centerY, float centerZ, float radiusX, float radiusY, float radiusZ) {

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
    }

    // Create the shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);

    // Link the shader program
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
    }

    GLuint vbo;
    GLuint vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);


    glBindVertexArray(vao);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Generate ellipse vertex data
    GLfloat vertexData[3 * numVertices];
    for (int i = 0; i < numVertices; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numVertices);
        vertexData[3 * i] = radiusX * cos(theta) + centerX;
        vertexData[3 * i + 1] = radiusY * sin(theta) + centerY;
        vertexData[3 * i + 2] = centerZ + radiusZ * sin(theta); // Vary the Z coordinate
    }

    // Copy the vertex data to the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // Specify the vertex attribute array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Use the shader program
    glUseProgram(shaderProgram);

}


int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Ellipse Drawing", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    drawEllipse(0.0f, 0.0f, 0.0f, 0.5f, 0.3f, 0.0f);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the ellipse using glDrawArrays
        glDrawArrays(GL_LINE_LOOP, 0, numVertices);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
