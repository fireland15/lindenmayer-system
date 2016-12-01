#pragma once

#include <memory>

#include "BaseRecorder.h"
#include "TurtleState.h"

namespace fli {
	namespace geometry_generator {
		class Turtle {
		private:
			TurtleState m_state;
			std::shared_ptr<BaseRecorder> mp_stateRecorder;

		public:
			Turtle(TurtleState initialState, std::shared_ptr<BaseRecorder> recorder)
				: m_state(initialState), mp_stateRecorder(recorder) {
				mp_stateRecorder->Record(initialState);
			}

			TurtleState GetState() {
				return m_state;
			}

			virtual void ExecuteCommand(std::function<void(TurtleState&)> func, bool shouldRecord) {
				func(m_state);
				if (shouldRecord) {
					PostExecute();
				}
			}

		private:
			virtual void PostExecute() {
				mp_stateRecorder->Record(m_state);
			}
		};
	}
}