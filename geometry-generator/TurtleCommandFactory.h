#pragma once

#include <memory>

#include "TurtleCommand.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"
#include "ITurtleCommandSet.h"

class TurtleCommandFactory {
private:
	std::unique_ptr<ITurtleCommandSet> m_commandSet;

public:
	TurtleCommandFactory(std::unique_ptr<ITurtleCommandSet> commandSet)
		: m_commandSet(std::move(commandSet)) { }

	TurtleCommand BuildCommand(LindenmayerSymbol symbol) {
		switch (symbol.GetSymbol()) {
		//Todo: Create a set of symbols to use.
		case 'F': // Forward length d, F(d)
			return TurtleCommand(m_commandSet->GetForwardCommand(symbol.GetParameters()[0]), true);
			break;
		case 'f': // Forward length d, f(d), without drawing
			return TurtleCommand(m_commandSet->GetForwardCommand(symbol.GetParameters()[0], true), true);
			break;
		case 'Y': // Yaw left by angle a, +(a)
			return TurtleCommand(m_commandSet->GetYawLeftCommand(symbol.GetParameters()[0]), false);
			break;
		case 'y': // Yaw right by angle a, -(a)
			return TurtleCommand(m_commandSet->GetYawRightCommand(symbol.GetParameters()[0]), false);
			break;
		case 'P': // Pitch down by angle a, &(a)
			return TurtleCommand(m_commandSet->GetPitchDownCommand(symbol.GetParameters()[0]), false);
			break;
		case 'p': // Pitch up by angle a, ^(a)
			return TurtleCommand(m_commandSet->GetPitchUpCommand(symbol.GetParameters()[0]), false);
			break;
		case 'R': // Roll left by angle a, \(a)
			return TurtleCommand(m_commandSet->GetRollLeftCommand(symbol.GetParameters()[0]), false);
			break;
		case 'r': // Roll right by angle a, /(a)
			return TurtleCommand(m_commandSet->GetRollRightCommand(symbol.GetParameters()[0]), false);
			break;
		case 'T': // Turn around |()
			return TurtleCommand(m_commandSet->GetTurnAroundCommand(), false);
			break;
		case 'B': // Push current state onto stack
			return TurtleCommand(m_commandSet->GetPushCommand(), false);
			break;
		case 'b': // Pop state from stack, without drawing
			return TurtleCommand(m_commandSet->GetPopCommand(), true);
			break;
		default:
			throw std::exception("Undefined symbol found");
		}
	}
};