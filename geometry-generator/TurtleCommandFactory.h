#pragma once

#include "TurtleCommand.h"
#include "../lindenmayer-system/lindenmayer-symbol.h"
#include "ITurtleCommandSet.h"

template <typename TState>
class TurtleCommandFactory {
private:
	ITurtleCommandSet m_commandSet;

public:
	TurtleCommandFactory(ITurtleCommandSet commandSet)
		: m_commandSet(commandSet) { }

	TurtleCommand<TState> BuildCommand(LindenmayerSymbol symbol) {
		switch (symbol.GetSymbol()) {
		//Todo: Create a set of symbols to use.
		case 'F': // Forward length d, F(d)
			return m_commandSet.GetForwardCommand(symbol.GetParameters()[0]);
			break;
		case 'f': // Forward length d, f(d), without drawing
			return m_commandSet.GetForwardCommand(symbol.GetParameters()[0], false);
			break;
		case '+': // Yaw left by angle a, +(a)
			return m_commandSet.GetYawLeftCommand(symbol.GetParameters()[0]);
			break;
		case '-': // Yaw right by angle a, -(a)
			return m_commandSet.GetYawRightCommand(symbol.GetParameters()[0]);
			break;
		case '&': // Pitch down by angle a, &(a)
			return m_commandSet.GetPitchDownCommand(symbol.GetParameters()[0]);
			break;
		case '^': // Pitch up by angle a, ^(a)
			return m_commandSet.GetPitchUpCommand(symbol.GetParameters()[0]);
			break;
		case '\\': // Roll left by angle a, \(a)
			return m_commandSet.GetRolLeftCommand(symbol.GetParameters()[0]);
			break;
		case '/': // Roll right by angle a, /(a)
			return m_commandSet.GetRollRightCommand(symbol.GetParameters()[0]);
			break;
		case '|': // Turn around |()
			return m_commandSet.GetTurnArroundCommand();
			break;
		case '[': // Push current state onto stack
			return m_commandSet.GetPushCommand();
			break;
		case ']': // Pop state from stack, without drawing
			return m_commandSet.GetPopCommand();
			break;
		default:
			throw std::exception("Undefined symbol found");
		}
	}
};