#pragma once

#include "BaseTurtle.h"
#include "BaseRecorder.h"

template <typename TState>
class RecordedTurtle : public BaseTurtle<TState> {
private:
	BaseRecorder<TState>& m_stateRecorder;

public:
	RecordedTurtle(TState initialState, BaseRecorder<TState>& recorder)
		: m_stateRecorder(recorder), BaseTurtle(initialState) {

	}

	virtual void ExecuteCommand(std::function<void(TState&)> func) {
		func(GetStateReference());
		PostExecute();
	}

protected:
	virtual void PostExecute() {
		m_stateRecorder.Record(GetState());
	}
};