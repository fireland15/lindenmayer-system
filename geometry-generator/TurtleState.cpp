#include "TurtleState.h"

namespace fli {
	namespace geometry_generator {
		TurtleState::TurtleState()
			: orientation(0.0f, 0.0f, 1.0f), position(0.0f, 0.0f, 0.0f) { }

		TurtleState::TurtleState(glm::vec3 up, glm::vec3 initialOrientation, glm::vec3 initialPosition)
			: orientation(initialOrientation), position(initialPosition) {}

		void TurtleState::PushState() {
			std::tuple<glm::vec3, glm::vec3> state(position, orientation);
			m_stateStack.push(state);
		}

		void TurtleState::PopState() {
			if (!m_stateStack.empty()) {
				std::tuple<glm::vec3, glm::vec3> state = m_stateStack.top();
				m_stateStack.pop();

				position = std::get<0>(state);
				orientation = std::get<1>(state);
			}
		}
	}
}