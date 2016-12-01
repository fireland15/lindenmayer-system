#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtx/rotate_vector.hpp"

#include "ITurtleCommandSet.h"
#include "TurtleState.h"

namespace fli {
	namespace geometry_generator {
		class VertexTurtleCommandSet : public ITurtleCommandSet {
		public:
			virtual TurtleCommandFunction GetForwardCommand(float length, bool draw = true) {
				return [length](TurtleState& state) {
					glm::vec3 pos = state.position;
					pos = pos + (glm::normalize(state.orientation) * length);
					state.position = pos;
				};
			}

			virtual TurtleCommandFunction GetYawLeftCommand(float angle) {
				return [angle](TurtleState& state) {
					glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
					state.orientation = glm::normalize(o);
				};
			}
			virtual TurtleCommandFunction GetYawRightCommand(float angle) {
				return [angle](TurtleState& state) {
					glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f));
					state.orientation = glm::normalize(o);
				};
			}
			virtual TurtleCommandFunction GetPitchDownCommand(float angle) {
				return [angle](TurtleState& state) {
					glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
					state.orientation = glm::normalize(o);
				};
			}
			virtual TurtleCommandFunction GetPitchUpCommand(float angle) {
				return [angle](TurtleState& state) {
					glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f));
					state.orientation = glm::normalize(o);
				};
			}
			virtual TurtleCommandFunction GetRollLeftCommand(float angle) {
				return [angle](TurtleState& state) {
					glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
					state.orientation = glm::normalize(o);
				};
			}
			virtual TurtleCommandFunction GetRollRightCommand(float angle) {
				return [angle](TurtleState& state) {
					glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
					state.orientation = glm::normalize(o);
				};
			}
			virtual TurtleCommandFunction GetTurnAroundCommand() {
				return [](TurtleState& state) {
					glm::vec3 o = glm::normalize(-1.0f * state.orientation);
					state.orientation = o;
				};

			}
			virtual TurtleCommandFunction GetPushCommand() {
				return [](TurtleState& state) {
					state.PushState();
				};

			}
			virtual TurtleCommandFunction GetPopCommand() {
				return [](TurtleState& state) {
					state.PopState();
				};
			}
		};
	}
}