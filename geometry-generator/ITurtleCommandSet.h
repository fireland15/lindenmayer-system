#pragma once
 
#include <functional>

#include "TurtleState.h"

typedef std::function<void(BaseTurtleState&)> BaseStateCmd;

template <typename TState>
class ITurtleCommandSet {
public:
	virtual std::function<void(TState&)> GetForwardCommand(float length, bool draw = true) = 0;
	virtual std::function<void(TState&)> GetYawLeftCommand(float angle) = 0;
	virtual std::function<void(TState&)> GetYawRightCommand(float angle) = 0;
	virtual std::function<void(TState&)> GetPitchDownCommand(float angle) = 0;
	virtual std::function<void(TState&)> GetPitchUpCommand(float angle) = 0;
	virtual std::function<void(TState&)> GetRollLeftCommand(float angle) = 0;
	virtual std::function<void(TState&)> GetRollRightCommand(float angle) = 0;
	virtual std::function<void(TState&)> GetTurnAroundCommand() = 0;
	virtual std::function<void(TState&)> GetPushCommand() = 0;
	virtual std::function<void(TState&)> GetPopCommand() = 0;
};