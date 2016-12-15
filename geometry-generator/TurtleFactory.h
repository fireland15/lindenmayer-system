#pragma once

#include <memory>

#include "BaseRecorder.h"
#include "TurtleState.h"
#include "Turtle.h"

namespace fli {
	namespace geometry_generator {
		class TurtleFactory {
		private:

		public:
			static std::unique_ptr<Turtle> MakeTurtle(std::shared_ptr<BaseRecorder> pRecorder);

		private:
			static TurtleState MakeInitState();
		};
	}
}