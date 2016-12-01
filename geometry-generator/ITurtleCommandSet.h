#pragma once
 
#include <functional>

#include "TurtleState.h"

typedef std::function<void(fli::geometry_generator::TurtleState&)> TurtleCommandFunction;

namespace fli {
	namespace geometry_generator {
		class ITurtleCommandSet {
		public:
			virtual TurtleCommandFunction GetForwardCommand(float length, bool draw = true) = 0;
			virtual TurtleCommandFunction GetYawLeftCommand(float angle) = 0;
			virtual TurtleCommandFunction GetYawRightCommand(float angle) = 0;
			virtual TurtleCommandFunction GetPitchDownCommand(float angle) = 0;
			virtual TurtleCommandFunction GetPitchUpCommand(float angle) = 0;
			virtual TurtleCommandFunction GetRollLeftCommand(float angle) = 0;
			virtual TurtleCommandFunction GetRollRightCommand(float angle) = 0;
			virtual TurtleCommandFunction GetTurnAroundCommand() = 0;
			virtual TurtleCommandFunction GetPushCommand() = 0;
			virtual TurtleCommandFunction GetPopCommand() = 0;
		};
	}
}