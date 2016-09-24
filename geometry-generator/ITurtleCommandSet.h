#pragma once
 
#include <functional>

#include "TurtleState.h"

typedef std::function<void(TurtleState&)> BaseStateCmd;

class ITurtleCommandSet {
public:
	virtual BaseStateCmd GetForwardCommand(float length, bool draw = true) = 0;
	virtual BaseStateCmd GetYawLeftCommand(float angle) = 0;
	virtual BaseStateCmd GetYawRightCommand(float angle) = 0;
	virtual BaseStateCmd GetPitchDownCommand(float angle) = 0;
	virtual BaseStateCmd GetPitchUpCommand(float angle) = 0;
	virtual BaseStateCmd GetRollLeftCommand(float angle) = 0;
	virtual BaseStateCmd GetRollRightCommand(float angle) = 0;
	virtual BaseStateCmd GetTurnAroundCommand() = 0;
	virtual BaseStateCmd GetPushCommand() = 0;
	virtual BaseStateCmd GetPopCommand() = 0;
};