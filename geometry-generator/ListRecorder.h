#pragma once

#include <vector>

#include "BaseRecorder.h"
#include "TurtleState.h"

class ListRecorder : public BaseRecorder {
private:
	std::vector<TurtleState> m_states;

public:
	virtual void Record(TurtleState state) {
		m_states.push_back(state);
	}

	const std::vector<TurtleState>& GetStates() {
		return m_states;
	}
};