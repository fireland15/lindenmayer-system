#pragma once

#include <functional>

#include "Turtle.h"
#include "TurtleState.h"

class TurtleCommand {
private:
	std::function<void(TurtleState&)> m_internalCommand;
	bool m_shouldRecordState;
	bool m_popState;
	bool m_pushState;

public:
	TurtleCommand(std::function<void(TurtleState&)> command, bool shouldRecordState)
		: m_internalCommand(command), m_shouldRecordState(shouldRecordState) { }

	void Execute(Turtle& turtle) {
		turtle.ExecuteCommand(m_internalCommand, m_shouldRecordState);
	}
};