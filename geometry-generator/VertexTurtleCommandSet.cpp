#include "VertexTurtleCommandSet.h"

namespace fli {
	namespace geometry_generator {
		TurtleCommandFunction WorldCentricCommandSet::GetForwardCommand(float length, bool draw = true) {
			return [length](TurtleState& state) {
				glm::vec3 pos = state.position;
				pos = pos + (glm::normalize(state.orientation) * length);
				state.position = pos;
			};
		}

		TurtleCommandFunction WorldCentricCommandSet::GetYawLeftCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction WorldCentricCommandSet::GetYawRightCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction WorldCentricCommandSet::GetPitchDownCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction WorldCentricCommandSet::GetPitchUpCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction WorldCentricCommandSet::GetRollLeftCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction WorldCentricCommandSet::GetRollRightCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction WorldCentricCommandSet::GetTurnAroundCommand() {
			return [](TurtleState& state) {
				glm::vec3 o = glm::normalize(-1.0f * state.orientation);
				state.orientation = o;
			};

		}
		TurtleCommandFunction WorldCentricCommandSet::GetPushCommand() {
			return [](TurtleState& state) {
				state.PushState();
			};

		}
		TurtleCommandFunction WorldCentricCommandSet::GetPopCommand() {
			return [](TurtleState& state) {
				state.PopState();
			};
		}
	}
}