#pragma once

#include <memory>

#include "BaseRecorder.h"
#include "EmptyRecorder.h"
#include "PointRecorder.h"
#include "GraphRecorder.h"
#include "Enums.h"

namespace fli {
	namespace geometry_generator {
		class RecorderFactory {
		public:
			static std::shared_ptr<BaseRecorder> MakeRecorder(RecorderType type);
		};
	}
}