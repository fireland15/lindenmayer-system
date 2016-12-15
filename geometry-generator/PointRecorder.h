#pragma once

#include <vector>

#include "TurtleState.h"
#include "BaseRecorder.h"

namespace fli {
	namespace geometry_generator {
		class PointRecorder : public BaseRecorder {
		private:
			std::vector<TurtleState> m_records;
		public:
			virtual void Record(TurtleState state);
			std::vector<TurtleState>& GetRecords();
		};
	}
}