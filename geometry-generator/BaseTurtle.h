#pragma once

#include <functional>

class BaseTurtle {
private:
	BaseTurtleState m_state;

public:
	BaseTurtle(BaseTurtleState state)
		: m_state(state) {

	}

	BaseTurtleState GetState() {
		return m_state;
	}

	void SetState(BaseTurtleState state) {
		m_state = state;
	}

	virtual void ExecuteCommand(std::function<void(BaseTurtleState&)> func) {
		func(m_state);
	}

protected:
	BaseTurtleState& GetStateReference() {
		return m_state;
	}
};