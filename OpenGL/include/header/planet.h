#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <__msvc_chrono.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/quaternion.hpp>

#define gravityConstant 100.0f

class Planet
{
public:
	glm::mat4 model;
	glm::vec3 position;
	glm::vec3 velocity;

    float mass;
    float radius;
    float rotateSpeed;

    GLuint vbo, vao;
    std::vector<glm::vec3> trail;

    Planet(glm::vec3 pos, float planetMass, glm::vec3 velo, float rad, float rSpeed);

    void gravityUpdate(Planet otherPlanet, float deltaTime);
    void drawTrail(float dt);
};