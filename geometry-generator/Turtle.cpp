#include "Turtle.h"

namespace fli {
	namespace geometry_generator {
		Turtle::Turtle(TurtleState initialState, std::shared_ptr<BaseRecorder> recorder)
			: m_state(initialState), mp_stateRecorder(recorder) {
			mp_stateRecorder->Record(initialState);
		}

		TurtleState Turtle::GetState() {
			return m_state;
		}

		void Turtle::ExecuteCommand(std::function<void(TurtleState&)> func, bool shouldRecord) {
			func(m_state);
			if (shouldRecord) {
				PostExecute();
			}
		}

		void Turtle::PostExecute() {
			mp_stateRecorder->Record(m_state);
		}
	}
}