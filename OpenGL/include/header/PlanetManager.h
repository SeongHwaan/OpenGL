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
    void loadPlanet(const std::string& name, const glm::vec3& position, const float& mass, const glm::vec3& velocity, const float& radius, const float& rotationSpeed);

    std::shared_ptr<Planet> getPlanet(const std::string& name);

    std::vector<std::shared_ptr<Planet>> getPlanetVector(const std::vector<std::string>& names);
};