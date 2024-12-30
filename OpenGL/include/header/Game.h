#pragma once

#include <iostream>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/projection.hpp>
#include "header/planet.h"
#include "header/player.h"

#define Radius 0.240559

class Game
{
public:
	Game();

	void checkCollision(Planet& o1, Player& o2);
};