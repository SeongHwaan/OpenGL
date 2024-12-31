#include "header/PlanetManager.h"

void PlanetManager::loadPlanet(const std::string& name, const glm::vec3& position, const float& mass, const glm::vec3& velocity, const float& radius, const float& rotationSpeed)
{
	planets[name] = std::make_shared<Planet>(name, position, mass, velocity, radius, rotationSpeed);
}

std::shared_ptr<Planet> PlanetManager::getPlanet(const std::string& name)
{
    if (planets.find(name) != planets.end())
    {
        return planets[name];
    }
    throw std::runtime_error("Planet not found: " + name);
}

std::vector<std::shared_ptr<Planet>> PlanetManager::getPlanetVector(const std::vector<std::string>& names) {
    std::vector<std::shared_ptr<Planet>> result;
    for (const auto& name : names) {
        auto planet = getPlanet(name);
        if (planet) {
            result.push_back(planet);
        }
    }
    return result;
}
