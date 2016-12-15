#include "TurtleFactory.h"

namespace fli {
	namespace geometry_generator {
		std::unique_ptr<Turtle> TurtleFactory::MakeTurtle(std::shared_ptr<BaseRecorder> pRecorder) {
			return std::unique_ptr<Turtle>(new Turtle(MakeInitState(), pRecorder));
		}

		TurtleState TurtleFactory::MakeInitState() {
			TurtleState initState;
			initState.position = glm::vec3(0.0f, 0.0f, 0.0f);
			initState.orientation = glm::vec3(0.0f, 1.0f, 0.0f);
			return initState;
		}
	}
}