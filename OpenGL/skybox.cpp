#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

#pragma once

class Skybox
{
public:

    GLuint skyboxVAO, skyboxVBO;
    std::vector<std::string> faces1;
    std::vector<std::string> faces2;
   
	Skybox() {
        float skyboxVertices[] = {
            // positions          
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        faces1 = {
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox3/skybox3_right1.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox3/skybox3_left2.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox3/skybox3_bottom4.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox3/skybox3_top3.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox3/skybox3_front5.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox3/skybox3_back6.png"
        };

        faces2 = {
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox2/skybox2_right1.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox2/skybox2_left2.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox2/skybox2_top3.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox2/skybox2_bottom4.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox2/skybox2_front5.png",
            "C:/Users/k9930/OpenGL/OpenGL/Shader/skybox/skybox2/skybox2_back6.png"
        };

        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}

    GLuint getVAO() {
        return skyboxVAO;
    }
};