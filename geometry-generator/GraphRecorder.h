#pragma once

#include "../glm/glm.hpp"

#include "BaseRecorder.h"
#include "Graph.h"

namespace fli {
	namespace geometry_generator {
		class GraphRecorder : public BaseRecorder {
		private:
			Graph<float, glm::vec3> m_graph;
			std::shared_ptr<Graph<float, glm::vec3>::Node> m_lastNode;

		public:
			virtual void Record(TurtleState state);
			Graph<float, glm::vec3> get_Graph();
		};
	}
}