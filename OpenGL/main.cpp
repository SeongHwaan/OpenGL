#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Shader/shader.h>
#include <Camera/camera.h>
#include <Model/model.h>

#include <filesystem>
#include <iostream>

#include "player.cpp"
#include "Game.cpp"
#include "skybox.cpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
unsigned int loadCubemap(std::vector<std::string> faces);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Player player = Player((glm::vec3(0.0f, 100.0f, 1000.0f)), glm::vec3(0.0f, 1.0f, 0.0f));

Camera camera(glm::vec3(110.0f, 110.0f, 00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Space", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    Shader normalShader("Shader/3.3_vertex.txt", "Shader/3.3_fragment.txt");
    Shader lightingShader("Shader/2.2.basic_lighting.txt", "Shader/2.2.basic_lightingfs.txt");
    Shader sunShader("Shader/2.2.basic_lighting.txt", "Shader/sun.txt");
    Shader lineShader("Shader/3.3_vertex.txt", "Shader/3.3_fragment_trail.txt");
    Shader skyboxShader("Shader/skybox.txt", "Shader/skyboxfs.txt");

    Model Sun("Shader/sun/sun.obj");
    Model AlienPlanet("Shader/AlienPlanet/AlienPlanet.obj");
    Model AlienPlanet2("Shader/AlienPlanet2/AlienPlanet.obj");
    Model AlienPlanet3("Shader/AlienPlanet3/AlienPlanet.obj");
    Model Mars("Shader/mars/Mars 2K.obj");
    Model Mercury("Shader/mercury/Mercury 1K.obj");
    Model Moon("Shader/moon/Moon 2K.obj");
    Model Venus("Shader/venus/Venus_1K.obj");

    Model Player("Shader/ufo/ufo/ufo.obj");

    Planet sun = Planet(glm::vec3(0.0f, 0.0f, 0.0f), 5000.0f, 
        glm::vec3(0.0f, 0.0f, 0.0f), 100.0f, 0.0f);
    Planet alienPlanet = Planet(glm::vec3(1.0f, 0.0f, 2000.0f), 10.0f, 
        glm::vec3(17.0f, 0.0f, .0f), 42.0f, 0.1f);
    Planet alienPlanet2 = Planet(glm::vec3(2000.0f, 0.0f, 0.0f), 0.5f,
        glm::vec3(-30.0f, 0.0f, 8.0f), 4.5f, 0.5f);
    Planet alienPlanet3 = Planet(glm::vec3(600.0f, 0.0f, 0.0f), 2.0f,
        glm::vec3(0.0f, 0.0f, -30.0f), 14.5f, 0.2f);
    Planet mars = Planet(glm::vec3(0.0f, 0.0f, 850.0f), 20.0f,
        glm::vec3(27.0f, 0.0f, 0.0f), 32.0f, 0.3f);
    Planet mercury = Planet(glm::vec3(400.0f, 0.0f, 0.0f), 1.0f,
        glm::vec3(0.0f, 0.0f, -35.0f), 22.0f, 0.1f);
    Planet moon = Planet(glm::vec3(-300.0f, 0.0f, -300.0f), 0.5f,
        glm::vec3(20.0f, 0.0f, -15.0f), 7.0f, 1.0f);
    Planet venus = Planet(glm::vec3(1500.0f, 0.0f, 0.0f), 10.0f,
        glm::vec3(0.0f, 0.0f, -21.0f), 42.0f, 0.1f);

    Game game = Game();
    Skybox skybox = Skybox();

    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);

    unsigned int cubemapTexture = loadCubemap(skybox.faces1);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = (currentFrame - lastFrame);
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.use();
        lightingShader.setVec3("light.position", lightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        // light properties
        lightingShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // material properties
        lightingShader.setFloat("material.shininess", 64.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(80.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        glm::mat4 sunModel = sun.model;
        glm::mat4 alienModel_1 = alienPlanet.model;
        glm::mat4 alienModel_2 = alienPlanet2.model;
        glm::mat4 alienModel_3 = alienPlanet3.model;
        glm::mat4 marsModel = mars.model;
        glm::mat4 mercuryModel = mercury.model;
        glm::mat4 moonModel = moon.model;
        glm::mat4 venusModel = venus.model;

        alienPlanet.gravityUpdate(sun, deltaTime);
        alienPlanet2.gravityUpdate(sun, deltaTime);
        alienPlanet3.gravityUpdate(sun, deltaTime);
        mars.gravityUpdate(sun, deltaTime);
        mercury.gravityUpdate(sun, deltaTime);
        moon.gravityUpdate(sun, deltaTime);
        venus.gravityUpdate(sun, deltaTime);

        lightingShader.setMat4("model", alienModel_1);
        AlienPlanet.Draw(lightingShader);

        lightingShader.setMat4("model", alienModel_2);
        AlienPlanet2.Draw(lightingShader);

        lightingShader.setMat4("model", alienModel_3);
        AlienPlanet3.Draw(lightingShader);

        lightingShader.setMat4("model", marsModel);
        Mars.Draw(lightingShader);

        lightingShader.setMat4("model", mercuryModel);
        Mercury.Draw(lightingShader);

        lightingShader.setMat4("model", moonModel);
        Moon.Draw(lightingShader);

        lightingShader.setMat4("model", venusModel);
        Venus.Draw(lightingShader);


        lightingShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
        lightingShader.setMat4("model", sunModel);
        Sun.Draw(lightingShader);

        player.gravityUpdate(sun, deltaTime);
        player.gravityUpdate(alienPlanet, deltaTime);
        player.gravityUpdate(alienPlanet2, deltaTime);
        player.gravityUpdate(alienPlanet3, deltaTime);
        player.gravityUpdate(mercury, deltaTime);
        player.gravityUpdate(mars, deltaTime);
        player.gravityUpdate(venus, deltaTime);

        glm::mat4 playerModel = player.final;
        lightingShader.setMat4("model", playerModel);

        if (!camera.getGodMode()) {
            player.render(camera);
        }
        else
            camera.Position = glm::vec3(100.0f, 1000.0f, 100.0f);

        Player.Draw(lightingShader);



        game.checkCollision(venus, player);
        game.checkCollision(mars, player);

        lineShader.use();
        lineShader.setMat4("projection", projection);
        lineShader.setMat4("view", view);
        lineShader.setMat4("model", glm::mat4(1.0f));

        alienPlanet.drawTrail(deltaTime);
        alienPlanet2.drawTrail(deltaTime);
        alienPlanet3.drawTrail(deltaTime);
        mercury.drawTrail(deltaTime);
        mars.drawTrail(deltaTime);
        moon.drawTrail(deltaTime);
        venus.drawTrail(deltaTime);

        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skybox.getVAO());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        camera.ProcessKeyboard(God, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        player.ProcessKeyboard(front, deltaTime, camera);
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        player.ProcessKeyboard(back, deltaTime,camera);
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        player.ProcessKeyboard(L, deltaTime, camera);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        player.ProcessKeyboard(R, deltaTime, camera);
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        player.ProcessKeyboard(Upp, deltaTime, camera);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        player.ProcessKeyboard(Down, deltaTime, camera);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}