#include "header/planet.h"

Planet::Planet(glm::vec3 pos, float planetMass, glm::vec3 velo, float rad, float rSpeed)
{
    position = pos;
    mass = planetMass;
    velocity = velo;
    radius = rad;
    rotateSpeed = rSpeed;

    model = glm::mat4(1.0f);

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 60000 * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Planet::gravityUpdate(Planet otherPlanet, float deltaTime)
{
    float gravityC = gravityConstant;
    glm::vec3 otherPosition = otherPlanet.position;

    float powDst = std::pow(glm::distance(position, otherPosition), 2);
    glm::vec3 norm = otherPosition - position;
    norm = glm::normalize(norm);

    glm::vec3 force = norm * (gravityC * mass * otherPlanet.mass / powDst);
    glm::vec3 acceleration = force / mass;
    glm::vec3 newVelocity = acceleration * deltaTime;
    velocity += newVelocity;
    position += velocity * deltaTime;

    model = glm::translate(glm::mat4(1.0f), position);
    model = glm::rotate(model, rotateSpeed * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, .0f));
}

void Planet::drawTrail(float dt)
{
    float speed = 0.5f;
    float angle = speed * dt;

    glm::vec3 newVel = -(glm::normalize(velocity) * radius);
    glm::vec3 newPos = position + newVel;

    trail.push_back(newPos);
    if (trail.size() > 60000) {
        trail.erase(trail.begin());
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, trail.size() * sizeof(glm::vec3), &trail[0]);
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, trail.size());
}