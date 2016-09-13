#pragma once

#include <vector>

#include "BaseRecorder.h"

template<typename TState>
class ListRecorder : public BaseRecorder<TState> {
private:
	std::vector<TState> m_states;

public:
	virtual void Record(TState state) {
		m_states.push_back(state);
	}

	const std::vector<TState>& GetStates() {
		return m_states;
	}
};