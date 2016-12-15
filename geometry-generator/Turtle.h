#pragma once

#include <memory>
#include <functional>

#include "BaseRecorder.h"
#include "TurtleState.h"

namespace fli {
	namespace geometry_generator {
		class Turtle {
		private:
			TurtleState m_state;
			std::shared_ptr<BaseRecorder> mp_stateRecorder;

		public:
			Turtle(TurtleState initialState, std::shared_ptr<BaseRecorder> recorder);

			TurtleState GetState();

			virtual void ExecuteCommand(std::function<void(TurtleState&)> func, bool shouldRecord);

		private:
			virtual void PostExecute();
		};
	}
}