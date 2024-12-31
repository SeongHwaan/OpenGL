#include "header/player.h"


Player::Player(glm::vec3 position, glm::vec3 up)
{
    Position = position;
    WorldUp = up;
    velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    deceleration = glm::vec3(2.0f);

    model = glm::mat4(1.0f);
    finalModel = glm::translate(model, position);

    radius = 0.5f;
    mass = 3.0;
    maxSpeed = 10.0f;
}

void Player::ProcessKeyboard(Player_Movement direction, float deltaTime, Camera& camera)
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

void Player::gravityUpdate(Planet* otherPlanet, float deltaTime)
{
    float gravityC = 30.0f;
    glm::vec3 otherPosition = otherPlanet->position;

    float powDst = std::pow(glm::distance(Position, otherPosition), 2);
    glm::vec3 norm = otherPosition - Position;
    norm = glm::normalize(norm);

    glm::vec3 force = norm * (gravityC * mass * otherPlanet->mass / powDst);
    glm::vec3 acceleration = force / mass;
    glm::vec3 newVelocity = acceleration * deltaTime;
    velocity += newVelocity;

    Position += velocity * deltaTime;
}

void Player::render(Camera& camera)
{
    camera.Position = Position;

    finalModel = glm::translate(glm::mat4(1.0f), Position);
    finalModel = glm::rotate(finalModel, glm::radians(camera.Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
}