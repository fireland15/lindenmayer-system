#include "TurtleCommand.h"

namespace fli {
	namespace geometry_generator {
		TurtleCommand::TurtleCommand(std::function<void(TurtleState&)> command, bool shouldRecordState)
			: m_internalCommand(command), m_shouldRecordState(shouldRecordState) { }

		void TurtleCommand::Execute(Turtle& turtle) {
			turtle.ExecuteCommand(m_internalCommand, m_shouldRecordState);
		}
	}
}