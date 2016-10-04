#pragma once

#include <vector>
#include <list>
#include <memory>

template <typename TEdgeAttribute, typename TNodeAttribute>
class Graph {
public:
	Graph() {

	}

	~Graph() {

	}

	class Node;

	class Edge {
	private:
		std::shared_ptr<Node> m_pNodeTo;
		TEdgeAttribute m_attribute;

	public:
		Edge(std::shared_ptr<Node> nodeTo, TEdgeAttribute attribute) {
			m_pNodeTo = nodeTo;
			m_attribute = attribute;
		}
	};

	class Node {
	private:
		std::vector<std::shared_ptr<Edge>> m_pEdgesOut;
		TNodeAttribute m_attribute;

	public:
		Node(TNodeAttribute attribute) {
			m_attribute = attribute;
		}

		~Node() {

		}

		void AddChild(std::shared_ptr<Node> child, TEdgeAttribute edgeAttribute) {
			std::shared_ptr<Edge> pEdge = std::shared_ptr<Edge>(new Edge(child, edgeAttribute));

			m_pEdgesOut.push_back(pEdge);
		}

		bool Equals(TNodeAttribute attribute) {
			return m_attribute == attribute;
		}
	};

	std::shared_ptr<Node> AddNode(TNodeAttribute nodeAttribute) {
		std::shared_ptr<Node> pNewNode = std::shared_ptr<Node>(new Node(nodeAttribute));

		if (m_pRootNode == nullptr) {
			m_pRootNode = pNewNode;
			m_pNodes.push_back(pNewNode);
		}
		else {
			return nullptr;
		}

		return pNewNode;
	}

	std::shared_ptr<Node> AddNode(std::shared_ptr<Node> parentNode, TNodeAttribute nodeAttribute, TEdgeAttribute edgeAttribute) {
		std::shared_ptr<Node> pNewNode = std::shared_ptr<Node>(new Node(nodeAttribute));
		m_pNodes.push_back(pNewNode);

		parentNode.get()->AddChild(pNewNode, edgeAttribute);

		return pNewNode;
	}

	bool IsEmpty() {
		return m_pNodes.empty();
	}

	std::shared_ptr<Node> FindNode(TNodeAttribute nodeAttribute) {
		for (std::shared_ptr<Node> node : m_pNodes) {
			if ((*node).Equals(nodeAttribute)) {
				return node;
			}
		}
		return nullptr;
	}

private:
	std::list<std::shared_ptr<Node>> m_pNodes;
	std::shared_ptr<Node> m_pRootNode = nullptr;
};