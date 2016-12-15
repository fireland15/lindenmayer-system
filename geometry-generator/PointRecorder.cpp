#include "PointRecorder.h"

namespace fli {
	namespace geometry_generator {
		void PointRecorder::Record(TurtleState state) {
			m_records.push_back(state);
		}

		std::vector<TurtleState>& PointRecorder::GetRecords() {
			return m_records;
		}
	}
}