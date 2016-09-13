#pragma once

#include <functional>

template <typename TState>
class BaseTurtle {
private:
	TState m_state;

public:
	BaseTurtle(TState state)
		: m_state(state) {

	}

	TState GetState() {
		return m_state;
	}

	void SetState(TState state) {
		m_state = state;
	}

	virtual void ExecuteCommand(std::function<void(TState&)> func) {
		func(m_state);
	}

protected:
	TState& GetStateReference() {
		return m_state;
	}
};