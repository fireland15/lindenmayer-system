#pragma once

#include "BaseTurtle.h"
#include "BaseRecorder.h"
#include "TurtleState.h"

class RecordedTurtle : public BaseTurtle {
private:
	BaseRecorder& m_stateRecorder;

public:
	RecordedTurtle(TurtleState initialState, BaseRecorder& recorder)
		: m_stateRecorder(recorder), BaseTurtle(initialState) {

	}

	virtual void ExecuteCommand(std::function<void(TurtleState&)> func) {
		func(GetStateReference());
		PostExecute();
	}

protected:
	virtual void PostExecute() {
		m_stateRecorder.Record(GetState());
	}
};