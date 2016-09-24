#pragma once

#include <functional>

#include "BaseTurtle.h"
#include "TurtleState.h"

class TurtleCommand {
private:
	std::function<void(TurtleState&)> m_internalCommand;

public:
	TurtleCommand(std::function<void(TurtleState&)> command) {
		m_internalCommand = command;
	}

	void Execute(BaseTurtle& turtle) {
		turtle.ExecuteCommand(m_internalCommand);
	}
};