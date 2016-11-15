#pragma once

#include "../glm/glm.hpp"

#include "BaseRecorder.h"
#include "Graph.h"

class GraphRecorder : public BaseRecorder {
private:
	Graph<float, glm::vec3> m_graph;
	std::shared_ptr<Graph<float, glm::vec3>::Node> m_lastNode;

public:
	virtual void Record(TurtleState state) {
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

	Graph<float, glm::vec3> get_Graph() {
		return m_graph;
	}
};