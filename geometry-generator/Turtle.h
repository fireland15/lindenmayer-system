#pragma once

#include <memory>

#include "BaseRecorder.h"
#include "TurtleState.h"

class Turtle {
private:
	TurtleState m_state;
	std::shared_ptr<BaseRecorder> mp_stateRecorder;

public:
	Turtle(TurtleState initialState, std::shared_ptr<BaseRecorder> recorder)
		: m_state(initialState), mp_stateRecorder(recorder) {

	}

	virtual void ExecuteCommand(std::function<void(TurtleState&)> func) {
		func(m_state);
		PostExecute();
	}

protected:
	virtual void PostExecute() {
		mp_stateRecorder->Record(m_state);
	}
};