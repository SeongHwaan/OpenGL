#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <Camera/camera.h>
#include "planet.cpp"

#pragma once

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


    Player(glm::vec3 position, glm::vec3 up)
    {
        Position = position;
        WorldUp = up;
        velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        deceleration = glm::vec3(2.0f);

        model = glm::mat4(1.0f);
        final = glm::translate(model, position);

        radius = 0.5f;
        mass = 3.0;
        maxSpeed = 10.0f;
    }

    void ProcessKeyboard(Player_Movement direction, float deltaTime, Camera& camera)
    {  
        float newAcceleration = 5.0f;

        glm::vec3 inputAcceleration = glm::vec3(0.0f);
        if (direction == front) {
            inputAcceleration = camera.Front;
        }
        else if (direction == back) {
            inputAcceleration = -camera.Front;
        }
        else if (direction == L) {
            inputAcceleration = -camera.Right;
        }
        else if (direction == R) {
            inputAcceleration = camera.Right;
        }
        else if (direction == Upp) {
            inputAcceleration = camera.Up;
        }
        else if (direction == Down) {
            inputAcceleration = -camera.Up;
        }

        acceleration = glm::normalize(inputAcceleration) * newAcceleration;

        velocity += acceleration * deltaTime;

        float speed = glm::length(velocity);
        if (speed > maxSpeed) {
            velocity = glm::normalize(velocity) * maxSpeed;
        }

        Position += velocity * deltaTime;
        acceleration = glm::vec3(0.0f);
    }

    void gravityUpdate(Planet& otherPlanet, float deltaTime) {
        float gravityC = 30.0f;
        glm::vec3 otherPosition = otherPlanet.position;
        
        float powDst = std::pow(glm::distance(Position, otherPosition), 2);
        glm::vec3 norm = otherPosition - Position;
        norm = glm::normalize(norm);

        glm::vec3 force = norm * (gravityC * mass * otherPlanet.mass / powDst);
        glm::vec3 acceleration = force / mass;
        glm::vec3 newVelocity = acceleration * deltaTime;
        velocity += newVelocity;

        Position += velocity * deltaTime;
    }

    void render(Camera& camera) {
        camera.Position = Position;

        final = glm::translate(glm::mat4(1.0f), Position);
        final = glm::rotate(final, glm::radians(camera.Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    }
};