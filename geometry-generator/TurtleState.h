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

			TurtleState()
				: orientation(0.0f, 0.0f, 1.0f), position(0.0f, 0.0f, 0.0f) { }

			TurtleState(glm::vec3 up, glm::vec3 initialOrientation, glm::vec3 initialPosition)
				: orientation(initialOrientation), position(initialPosition) {}

			void PushState() {
				std::tuple<glm::vec3, glm::vec3> state(position, orientation);
				m_stateStack.push(state);
			}

			void PopState() {
				if (!m_stateStack.empty()) {
					std::tuple<glm::vec3, glm::vec3> state = m_stateStack.top();
					m_stateStack.pop();

					position = std::get<0>(state);
					orientation = std::get<1>(state);
				}
			}
		};
	}
}