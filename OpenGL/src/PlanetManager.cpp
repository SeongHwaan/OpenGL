#include "header/PlanetManager.h"

void PlanetManager::loadPlanet(const std::string& name, glm::vec3 position, float mass, glm::vec3 velocity, float radius, float rotationSpeed)
{
	planets[name] = std::make_shared<Planet>(position, mass, velocity, radius, rotationSpeed);
}

std::shared_ptr<Planet> PlanetManager::getPlanet(const std::string& name)
{
    if (planets.find(name) != planets.end())
    {
        return planets[name];
    }
    throw std::runtime_error("Planet not found: " + name);
}
