#include "TurtleCentricCommandSet.h"

namespace fli {
	namespace geometry_generator {
		TurtleCommandFunction TurtleCentricCommandSet::GetForwardCommand(float length, bool draw = true) {
			return [length](TurtleState& state) {
				glm::vec3 pos = state.position;
				pos = pos + (glm::normalize(state.orientation) * length);
				state.position = pos;
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetYawLeftCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), state.up);
				state.orientation = glm::normalize(o);
				state.up = glm::normalize(math::projectToPlane(state.orientation, state.up));
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetYawRightCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), state.up);
				state.orientation = glm::normalize(o);
				state.up = glm::normalize(math::projectToPlane(state.orientation, state.up));
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetPitchDownCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::normalize(glm::cross(state.orientation, state.up)));
				state.orientation = glm::normalize(o);
				state.up = glm::normalize(math::projectToPlane(state.orientation, state.up));
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetPitchUpCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::normalize(glm::cross(state.orientation, state.up)));
				state.orientation = glm::normalize(o);
				state.up = glm::normalize(math::projectToPlane(state.orientation, state.up));
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetRollLeftCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 up = glm::rotate(state.up, glm::radians(angle), state.orientation);
				state.up = glm::normalize(up);
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetRollRightCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 up = glm::rotate(state.up, glm::radians(-angle), state.orientation);
				state.up = glm::normalize(up);
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetTurnAroundCommand() {
			return [](TurtleState& state) {
				glm::vec3 o = glm::normalize(-1.0F * state.orientation);
				state.orientation = o;
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetPushCommand() {
			return [](TurtleState& state) {
				state.PushState();
			};
		}

		TurtleCommandFunction TurtleCentricCommandSet::GetPopCommand() {
			return [](TurtleState& state) {
				state.PopState();
			};
		}
	}
}