#pragma once

#include <stack>
#include <tuple>

#include "../glm/glm.hpp"

namespace fli {
	namespace geometry_generator {
		struct TurtleState {
			glm::vec3 orientation;
			glm::vec3 position;

			std::stack<std::tuple<glm::vec3, glm::vec3>> m_stateStack;

			TurtleState();

			TurtleState(glm::vec3 up, glm::vec3 initialOrientation, glm::vec3 initialPosition);

			void PushState();

			void PopState();
		};
	}
}