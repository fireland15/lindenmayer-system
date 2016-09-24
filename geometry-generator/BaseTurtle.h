#pragma once

#include <functional>

#include "TurtleState.h"

class BaseTurtle {
private:
	TurtleState m_state;

public:
	BaseTurtle(TurtleState state)
		: m_state(state) {

	}

	TurtleState GetState() {
		return m_state;
	}

	void SetState(TurtleState state) {
		m_state = state;
	}

	virtual void ExecuteCommand(std::function<void(TurtleState&)> func) {
		func(m_state);
	}

protected:
	TurtleState& GetStateReference() {
		return m_state;
	}
};