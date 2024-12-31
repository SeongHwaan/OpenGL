#pragma once

#include <map>
#include <string>
#include <memory>
#include "header/planet.h"

class PlanetManager 
{
private:
    std::map<std::string, std::shared_ptr<Planet>> planets;

public:
    void loadPlanet(const std::string& name, glm::vec3 position, float mass, glm::vec3 velocity, float radius, float rotationSpeed);

    std::shared_ptr<Planet> getPlanet(const std::string& name);
};