#include "GraphRecorder.h"

namespace fli {
	namespace geometry_generator {
		void GraphRecorder::Record(TurtleState state) {
			if (m_graph.IsEmpty()) {
				m_lastNode = m_graph.AddNode(state.position);
				return;
			}

			std::shared_ptr<Graph<float, glm::vec3>::Node> node = m_graph.FindNode(state.position);

			if (node == nullptr) {
				m_lastNode = m_graph.AddNode(m_lastNode, state.position, 0.0f);
			}
			else {
				m_lastNode = node;
			}
		}

		Graph<float, glm::vec3> GraphRecorder::get_Graph() {
			return m_graph;
		}
	}
}