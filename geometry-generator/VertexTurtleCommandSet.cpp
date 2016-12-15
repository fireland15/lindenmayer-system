#include "VertexTurtleCommandSet.h"

namespace fli {
	namespace geometry_generator {
		TurtleCommandFunction VertexTurtleCommandSet::GetForwardCommand(float length, bool draw = true) {
			return [length](TurtleState& state) {
				glm::vec3 pos = state.position;
				pos = pos + (glm::normalize(state.orientation) * length);
				state.position = pos;
			};
		}

		TurtleCommandFunction VertexTurtleCommandSet::GetYawLeftCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction VertexTurtleCommandSet::GetYawRightCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction VertexTurtleCommandSet::GetPitchDownCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction VertexTurtleCommandSet::GetPitchUpCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction VertexTurtleCommandSet::GetRollLeftCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction VertexTurtleCommandSet::GetRollRightCommand(float angle) {
			return [angle](TurtleState& state) {
				glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
				state.orientation = glm::normalize(o);
			};
		}
		TurtleCommandFunction VertexTurtleCommandSet::GetTurnAroundCommand() {
			return [](TurtleState& state) {
				glm::vec3 o = glm::normalize(-1.0f * state.orientation);
				state.orientation = o;
			};

		}
		TurtleCommandFunction VertexTurtleCommandSet::GetPushCommand() {
			return [](TurtleState& state) {
				state.PushState();
			};

		}
		TurtleCommandFunction VertexTurtleCommandSet::GetPopCommand() {
			return [](TurtleState& state) {
				state.PopState();
			};
		}
	}
}