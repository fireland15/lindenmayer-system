#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtx/rotate_vector.hpp"

#include "ITurtleCommandSet.h"
#include "TurtleState.h"

class VertexTurtleCommandSet : public ITurtleCommandSet<BaseTurtleState> {
public:
	virtual BaseStateCmd GetForwardCommand(float length, bool draw = true) {
		return [length](BaseTurtleState& state) {
			glm::vec3 pos = state.position;
			pos = pos + (glm::normalize(state.orientation) * length);
			state.position = pos;
		};
	}

	virtual BaseStateCmd GetYawLeftCommand(float angle) {
		return [angle](BaseTurtleState& state) {
			glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			state.orientation = glm::normalize(o);
		};
	}
	virtual BaseStateCmd GetYawRightCommand(float angle) {
		return [angle](BaseTurtleState& state) { 
			glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f));
			state.orientation = glm::normalize(o);
		};
	}
	virtual BaseStateCmd GetPitchDownCommand(float angle) {
		return [angle](BaseTurtleState& state) { 
			glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
			state.orientation = glm::normalize(o);
		};
	}
	virtual BaseStateCmd GetPitchUpCommand(float angle) {
		return [angle](BaseTurtleState& state) { 
			glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f));
			state.orientation = glm::normalize(o);
		};
	}
	virtual BaseStateCmd GetRollLeftCommand(float angle) {
		return [angle](BaseTurtleState& state) {
			glm::vec3 o = glm::rotate(state.orientation, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
			state.orientation = glm::normalize(o);
		};
	}
	virtual BaseStateCmd GetRollRightCommand(float angle) {
		return [angle](BaseTurtleState& state) { 
			glm::vec3 o = glm::rotate(state.orientation, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
			state.orientation = glm::normalize(o);
		};
	}
	virtual BaseStateCmd GetTurnAroundCommand() {
		return [](BaseTurtleState& state) { return state; };

	}
	virtual BaseStateCmd GetPushCommand() {
		return [](BaseTurtleState& state) { return state; };

	}
	virtual BaseStateCmd GetPopCommand() {
		return [](BaseTurtleState& state) { return state; };

	}
};