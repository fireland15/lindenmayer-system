#pragma once

#include <functional>

#include "BaseTurtle.h"

template <typename TState>
class TurtleCommand {
private:
	std::function<void(TState&)> m_internalCommand;

public:
	TurtleCommand(std::function<void(TState&)> command) {
		m_internalCommand = command;
	}

	void Execute(BaseTurtle<TState>& turtle) {
		turtle.ExecuteCommand(m_internalCommand);
	}
};