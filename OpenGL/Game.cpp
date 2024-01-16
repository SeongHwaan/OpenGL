#include <iostream>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/projection.hpp>
#include "planet.cpp"
#include "player.cpp"
#pragma once

#define Radius 0.240559

class Game
{
public:
	Game() {}

	void checkCollision(Planet& o1, Player& o2)
	{
		float xDiff = (o1.position.x - o2.Position.x) * (o1.position.x - o2.Position.x);
		float yDiff = (o1.position.y - o2.Position.y) * (o1.position.y - o2.Position.y);
		float zDiff = (o1.position.z - o2.Position.z) * (o1.position.z - o2.Position.z);

		float sumOfDiff = xDiff + yDiff + zDiff;
		float planetRadius = o1.radius;
		float playerRadius = o2.radius;


		if (sqrt(sumOfDiff) < planetRadius + playerRadius) {
			std::cout << "collision! ";
			glm::vec3 norm = glm::normalize(o2.Position - o1.position);
			glm::vec3 a = norm * planetRadius ; //radius
			o2.Position = o1.position + a;
		}
	}
};