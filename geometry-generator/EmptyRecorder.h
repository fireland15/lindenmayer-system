#pragma once

#include "TurtleState.h"
#include "BaseRecorder.h"

namespace fli {
	namespace geometry_generator {
		class EmptyRecorder : public BaseRecorder {
		private:

		public:
			virtual void Record(TurtleState state);
		};
	}
}