#pragma once

#include "../glm/glm.hpp"
#include "../glm/gtx/rotate_vector.hpp"

#include "ITurtleCommandSet.h"
#include "TurtleState.h"

namespace fli {
	namespace geometry_generator {
		class VertexTurtleCommandSet : public ITurtleCommandSet {
		public:
			virtual TurtleCommandFunction GetForwardCommand(float length, bool draw);

			virtual TurtleCommandFunction GetYawLeftCommand(float angle);

			virtual TurtleCommandFunction GetYawRightCommand(float angle);

			virtual TurtleCommandFunction GetPitchDownCommand(float angle);

			virtual TurtleCommandFunction GetPitchUpCommand(float angle);

			virtual TurtleCommandFunction GetRollLeftCommand(float angle);

			virtual TurtleCommandFunction GetRollRightCommand(float angle);

			virtual TurtleCommandFunction GetTurnAroundCommand();

			virtual TurtleCommandFunction GetPushCommand();

			virtual TurtleCommandFunction GetPopCommand();
		};
	}
}