#pragma once

#include <vector>

#include "BaseRecorder.h"
#include "TurtleState.h"

class ListRecorder : public BaseRecorder {
private:
	std::vector<BaseTurtleState> m_states;

public:
	virtual void Record(BaseTurtleState state) {
		m_states.push_back(state);
	}

	const std::vector<BaseTurtleState>& GetStates() {
		return m_states;
	}
};