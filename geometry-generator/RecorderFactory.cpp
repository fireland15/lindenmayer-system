#include "RecorderFactory.h"

namespace fli {
	namespace geometry_generator {
		std::shared_ptr<BaseRecorder> RecorderFactory::MakeRecorder(RecorderType type) {
			switch (type) {
			case RecorderType::Empty:
				return std::shared_ptr<BaseRecorder>(new EmptyRecorder);
			case RecorderType::Point:
				return std::shared_ptr<BaseRecorder>(new PointRecorder);
			case RecorderType::Graph:
				return std::shared_ptr<BaseRecorder>(new GraphRecorder);
			default:
				return nullptr;
			}
		}
	}
}