#pragma once

#include <functional>

#include "BaseTurtle.h"

class TurtleCommand {
private:
	std::function<void(BaseTurtleState&)> m_internalCommand;

public:
	TurtleCommand(std::function<void(BaseTurtleState&)> command) {
		m_internalCommand = command;
	}

	void Execute(BaseTurtle& turtle) {
		turtle.ExecuteCommand(m_internalCommand);
	}
};