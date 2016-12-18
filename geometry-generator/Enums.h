#pragma once

namespace fli {
	namespace geometry_generator {
		enum class GeometryType {
			Points,
			Lines,
			Tubes,
			Smooth
		};

		enum class RecorderType {
			Empty,
			Point,
			Graph
		};

		enum class TurtleType {
			Base,
			ListRecorded
		};

		enum class TurtleCommandSetType {
			TurtleCentric,
			WorldCentric
		};
	}
}