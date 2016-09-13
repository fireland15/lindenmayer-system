#pragma once

#include "../glm/glm.hpp"

struct BaseTurtleState {
	glm::vec3 up;
	glm::vec3 orientation;
	glm::vec3 position;

	BaseTurtleState()
		: up(0.0f, 1.0f, 0.0f), orientation(0.0f, 0.0f, 1.0f), position(0.0f, 0.0f, 0.0f) { }

	BaseTurtleState(glm::vec3 up, glm::vec3 initialOrientation, glm::vec3 initialPosition) 
		: up(up), orientation(initialOrientation), position(initialPosition) {}
};