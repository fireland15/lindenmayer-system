#include "binary-operator-node.h"

BinaryOperatorNode::BinaryOperatorNode(std::function<float(float, float)> operation)
	:m_operation(operation) { }

float BinaryOperatorNode::operator()() {
	return m_operation((*m_child[0])(), (*m_child[1])());
}

void BinaryOperatorNode::Delete() {
	m_child[0]->Delete();
	m_child[1]->Delete();

	delete m_child[0];
	delete m_child[1];
}

unsigned int BinaryOperatorNode::NumChildren() { 
	return 2; 
}

void BinaryOperatorNode::SetChild(ExpressionNode* child, unsigned int i) {
	if (i >= 2)
		throw std::runtime_error("cannot set child at index: " + i);

	m_child[i] = child;
}