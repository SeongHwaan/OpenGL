#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <Camera/camera.h>
#include "header/planet.h"

enum Player_Movement {
    front,
    back,
    L,
    R,
    Upp,
    Down,
};

class Player
{
public:
    glm::mat4 model;
    glm::mat4 final;

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 deceleration;
    glm::vec3 view;

    float maxSpeed;
    float radius;
    float mass;


    Player(glm::vec3 position, glm::vec3 up);

    void ProcessKeyboard(Player_Movement direction, float deltaTime, Camera& camera);
    void gravityUpdate(Planet& otherPlanet, float deltaTime);
    void render(Camera& camera);
};