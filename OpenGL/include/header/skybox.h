#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

class Skybox
{
public:

    GLuint skyboxVAO, skyboxVBO;
    std::vector<std::string> faces1;
    std::vector<std::string> faces2;
   
    Skybox();

    GLuint getVAO();
};