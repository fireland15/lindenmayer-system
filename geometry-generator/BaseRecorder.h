#pragma once

#include "TurtleState.h"

namespace fli {
	namespace geometry_generator {
		class BaseRecorder {
		private:

		public:
			virtual void Record(TurtleState state) = 0;
		};
	}
}