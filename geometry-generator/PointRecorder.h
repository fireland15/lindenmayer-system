#pragma once

#include <vector>

#include "TurtleState.h"

namespace fli {
	namespace geometry_generator {
		class PointRecorder : public BaseRecorder {
		private:
			std::vector<TurtleState> m_records;
		public:
			virtual void Record(TurtleState state) {
				m_records.push_back(state);
			}

			std::vector<TurtleState>& GetRecords() {
				return m_records;
			}
		};
	}
}